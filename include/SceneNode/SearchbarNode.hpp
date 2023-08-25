#pragma once

#include <SceneNode.hpp>

class SearchbarNode 
: public SceneNode
{
public:
    enum class Alignment
    {
        TopLeft,
        TopCenter,
        TopRight,
        CenterLeft,
        Center,
        CenterRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };

private:
    sf::RectangleShape mBackground;
    sf::Text           mText;
    sf::Text           mHintText;
    float              mMarginVertical;
    float              mMarginHorizontal;

public:
    SearchbarNode(Activity::Context* context);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture);
    virtual sf::FloatRect getLocalBounds() const;
    void setMarginVertical(float margin);
    void setMarginHorizontal(float margin);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};