#pragma once

#include <SceneNode.hpp>

class ButtonNode
: public SceneNode
{
private:
    sf::VertexArray mBackground;
    sf::Text        mText;

public:
    ButtonNode(Activity::Context* context);
    ButtonNode(Activity::Context* context, const sf::Vector2f& size);
    ButtonNode(Activity::Context* context, const sf::Vector2f& size, const std::string& text);
    ButtonNode(Activity::Context* context, const sf::Vector2f& size, const std::string& text, unsigned int characterSize);
    void setSize(const sf::Vector2f& size);
    void setBackgroundColor(const sf::Color& color);
    void setText(const std::string& text);
    void setTextColor(const sf::Color& color);
    virtual sf::FloatRect   getLocalBounds() const;
    void setListeners();

private:
    virtual bool            contains(const sf::Vector2f& point) const;
    bool                    contains(const sf::Vector2f& point, const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) const;
    virtual void            drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void            updateCurrent(sf::Time dt);
};