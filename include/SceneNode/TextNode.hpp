#pragma once

#include <SceneNode.hpp>

class TextNode 
: public SceneNode
, public sf::Text
{
public:
    TextNode(Activity::Context* context);
    TextNode(Activity::Context* context, const std::string& text);
    TextNode(Activity::Context* context, const std::string& text, const sf::Font& font);
    TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize);
    TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color);
    virtual sf::FloatRect getLocalBounds() const;
    void setString(const std::string& text);
    void alignCenter();

private:
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};