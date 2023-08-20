#include <SceneNode/TextNode.hpp>

TextNode::TextNode(Activity::Context* context)
: SceneNode(context)
, sf::Text()
{
}

TextNode::TextNode(Activity::Context* context, const std::string& text)
: SceneNode(context)
, sf::Text(text, context->fonts->get(Fonts::DEFAULT), 30)
{
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font)
: SceneNode(context)
, sf::Text(text, font, 30)
{
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize)
: SceneNode(context)
, sf::Text(text, font, characterSize)
{
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color)
: SceneNode(context)
, sf::Text(text, font, characterSize)
{
    setColor(color);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*(static_cast<const sf::Text*>(this)), states);
}

sf::FloatRect TextNode::getLocalBounds() const
{
    return Text::getLocalBounds();
}

void TextNode::alignCenter()
{
    sf::FloatRect bounds = getLocalBounds();
    SceneNode::setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}