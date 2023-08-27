#include <SceneNode\RectangleNode.hpp>

RectangleNode::RectangleNode(Activity::Context* context)
: sf::RectangleShape()
, SceneNode(context)
{
}

RectangleNode::RectangleNode(Activity::Context* context, const sf::Vector2f& size)
: sf::RectangleShape(size)
, SceneNode(context)
{
}

RectangleNode::RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color)
: sf::RectangleShape(size)
, SceneNode(context)
{
    this->setFillColor(color);
}

RectangleNode::RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture)
: sf::RectangleShape(size)
, SceneNode(context)
{
    this->setTexture(&texture);
}

RectangleNode::RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& textureRect)
: sf::RectangleShape(size)
, SceneNode(context)
{
    this->setTexture(&texture);
    this->setTextureRect(textureRect);
}

void RectangleNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*(static_cast<const sf::RectangleShape*>(this)), states);
}

sf::FloatRect RectangleNode::getLocalBounds() const
{
    return RectangleShape::getLocalBounds();
}