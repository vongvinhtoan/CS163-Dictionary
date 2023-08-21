#include <iostream>
#include <SceneNode/ButtonNode.hpp>

ButtonNode::ButtonNode(Activity::Context* context)
: SceneNode(context)
, mBackground(sf::TriangleStrip, 6)
, mText("", context->fonts->get(Fonts::DEFAULT))
{
    setSize(sf::Vector2f(0.f, 0.f));
    setListeners();
}

ButtonNode::ButtonNode(Activity::Context* context, const sf::Vector2f& size)
: SceneNode(context)
, mBackground(sf::TriangleStrip, 6)
, mText("", context->fonts->get(Fonts::DEFAULT))
{
    setSize(size);
    setListeners();
}

ButtonNode::ButtonNode(Activity::Context* context, const sf::Vector2f& size, const std::string& text)
: SceneNode(context)
, mBackground(sf::TriangleStrip, 6)
, mText(text, context->fonts->get(Fonts::DEFAULT))
{
    setSize(size);
    setListeners();
}

ButtonNode::ButtonNode(Activity::Context* context, const sf::Vector2f& size, const std::string& text, unsigned int characterSize)
: SceneNode(context)
, mBackground(sf::TriangleStrip, 6)
, mText(text, context->fonts->get(Fonts::DEFAULT), characterSize)
{
    setSize(size);
    setListeners();
}

void ButtonNode::setBackgroundColor(const sf::Color& color)
{
    for(int i = 0; i < 6; i++)
    {
        mBackground[i].color = color;
    }
}

void ButtonNode::setText(const std::string& text)
{
    mText.setString(text);
}

void ButtonNode::setListeners()
{
    SceneNode::mOnHover = [](SceneNode& node) {
        ((ButtonNode&)node).setBackgroundColor(sf::Color(0x5A5A5AFF));
    };

    SceneNode::mOnLostHover = [](SceneNode& node) {
        ((ButtonNode&)node).setBackgroundColor(sf::Color(0xA02C2CFF));
    };

    SceneNode::mOnHold = [](SceneNode& node) {
        ((ButtonNode&)node).setBackgroundColor(sf::Color(0x2C2CA0FF));
    };
}

void ButtonNode::setSize(const sf::Vector2f& size)
{
    float w = size.x;
    float h = size.y;
    mBackground[0] = sf::Vertex(sf::Vector2f(0.f, h/2), sf::Color(0xA02C2CFF));
    mBackground[1] = sf::Vertex(sf::Vector2f(h/2, 0.f), sf::Color(0xA02C2CFF));
    mBackground[2] = sf::Vertex(sf::Vector2f(h/2, h), sf::Color(0xA02C2CFF));
    mBackground[3] = sf::Vertex(sf::Vector2f(w-h/2, 0.f), sf::Color(0xA02C2CFF));
    mBackground[4] = sf::Vertex(sf::Vector2f(w-h/2, h), sf::Color(0xA02C2CFF));
    mBackground[5] = sf::Vertex(sf::Vector2f(w, h/2), sf::Color(0xA02C2CFF));
}

void ButtonNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);
    target.draw(mText, states);
}

void ButtonNode::updateCurrent(sf::Time dt)
{
    sf::FloatRect bounds = mText.getLocalBounds();
    mText.setOrigin(bounds.left + bounds.width/2.f, bounds.top + bounds.height/2.f);
    mText.setPosition(getLocalBounds().width/2.f, getLocalBounds().height/2.f);
}

bool ButtonNode::contains(const sf::Vector2f& point) const
{
    for(int i = 2; i < 6; i++) 
    {
        if(contains(point, mBackground[i-2].position, mBackground[i-1].position, mBackground[i].position))
        {
            return true;
        }
    }
    return false;
}

bool ButtonNode::contains(const sf::Vector2f& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) const
{
    float as_x = point.x-a.x;
    float as_y = point.y-a.y;

    bool s_ab = (b.x-a.x)*as_y-(b.y-a.y)*as_x > 0;

    if((c.x-a.x)*as_y-(c.y-a.y)*as_x > 0 == s_ab) return false;

    if((c.x-b.x)*(point.y-b.y)-(c.y-b.y)*(point.x-b.x) > 0 != s_ab) return false;

    return true;
}

sf::FloatRect ButtonNode::getLocalBounds() const
{
    return sf::FloatRect(0.f, 0.f, mBackground[5].position.x, mBackground[2].position.y);
}