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
    sf::RectangleShape mCursor;
    sf::Text           mText;
    sf::Text           mHintText;
    sf::Time           mCursorTime;
    float              mMarginVertical;
    float              mMarginHorizontal;
    std::string        mHintString;
    std::string        mString;
    Alignment          mAlignment;
    bool               mIsFocused;
    bool               mCursorVisible;

public:
    SearchbarNode(Activity::Context* context);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color);
    SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture);
    virtual sf::FloatRect getLocalBounds() const;
    void setMarginVertical(float margin);
    void setMarginHorizontal(float margin);
    void setAlignment(Alignment alignment);
    void setHint(const std::string& hint);
    bool isFocused() const;
    void setOnEnter(std::function<void(SceneNode&)> onEnter);
    void setCharacterSize(unsigned int size);
    void setFont(const sf::Font& font);
    void clear();
    std::string getString() const;

private:
    const float mCursorWidth = 2.f;
    const sf::Time mCursorBlinkTime = sf::seconds(0.5f);
    std::function<void(SceneNode&)> mOnEnter;

    virtual void handleEventCurrent(const sf::Event& event, int& command);
    virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void updateCurrent(sf::Time dt);
    void fixTextsPosition();
    void setListeners();
    void putText();
};