#pragma once

#include <SceneNode.hpp>

class SearchbarNode 
: public SceneNode
{
public:
    enum Alignment
    {
        Left = (1<<0),
        Middle = (1<<1),
        Right = (1<<2),
        Top = (1<<3),
        Bottom = (1<<4),
        Center = (1<<5)
    };

private:
    sf::RectangleShape mBackground;
    sf::Text           mText;
    sf::Text           mHintText;
    float              mMarginVertical;
    float              mMarginHorizontal;
    std::string        mHintString;
    std::string        mString;
    Alignment          mAlignment;

public:
    SearchbarNode(Activity::Context* context);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture);
    virtual sf::FloatRect getLocalBounds() const;
    void setMarginVertical(float margin);
    void setMarginHorizontal(float margin);
    void setAlignment(Alignment alignment);

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    void fixTextsPosition();
};