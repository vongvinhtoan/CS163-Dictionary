#pragma once

#include <SceneNode.hpp>

// Inherit from SceneNode and RectangleShape
class RectangleNode 
: public SceneNode
, public sf::RectangleShape
{
public:
    RectangleNode(Activity::Context* context);
    RectangleNode(Activity::Context* context, const sf::Vector2f& size);
    RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color);
    RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture);
    RectangleNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture, const sf::IntRect& textureRect);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual sf::FloatRect getLocalBounds() const;
};