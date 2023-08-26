#include <SceneNode/SearchbarNode.hpp>
#include <iostream>

SearchbarNode::SearchbarNode(Activity::Context* context)
: SceneNode(context)
, mBackground()
, mText()
, mHintText()
, mHintString()
, mString()
, mMarginVertical(0.f)
, mMarginHorizontal(0.f)
, mAlignment(Alignment(Top | Left))
, mIsFocused(false)
, mCursor(sf::Vector2f(mCursorWidth, 0.f))
, mCursorTime(sf::Time::Zero)
, mCursorVisible(false)
{
    mHintText.setColor(sf::Color(0xC1C1C1FF));
    mText.setColor(sf::Color::Black);
    fixTextsPosition();
    mCursor.setFillColor(sf::Color::Black);
    putText();

    setListeners();
}

SearchbarNode::SearchbarNode(Activity::Context* context, const sf::Vector2f& size)
: SceneNode(context)
, mBackground(size)
, mText()
, mHintText()
, mHintString()
, mString()
, mMarginVertical(0.f)
, mMarginHorizontal(0.f)
, mAlignment(Alignment(Top | Left))
, mIsFocused(false)
, mCursor(sf::Vector2f(mCursorWidth, 0.f))
, mCursorTime(sf::Time::Zero)
, mCursorVisible(false)
{
    mHintText.setColor(sf::Color(0xC1C1C1FF));
    mText.setColor(sf::Color::Black);
    fixTextsPosition();
    mCursor.setFillColor(sf::Color::Black);
    putText();

    setListeners();
}

SearchbarNode::SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Color& color)
: SceneNode(context)
, mBackground(size)
, mText()
, mHintText()
, mHintString()
, mString()
, mMarginVertical(0.f)
, mMarginHorizontal(0.f)
, mAlignment(Alignment(Top | Left))
, mIsFocused(false)
, mCursor(sf::Vector2f(mCursorWidth, 0.f))
, mCursorTime(sf::Time::Zero)
, mCursorVisible(false)
{
    mHintText.setColor(sf::Color(0xC1C1C1FF));
    mText.setColor(sf::Color::Black);
    fixTextsPosition();
    mBackground.setFillColor(color);
    mCursor.setFillColor(sf::Color::Black);
    putText();

    setListeners();
}

SearchbarNode::SearchbarNode(Activity::Context* context, const sf::Vector2f& size, const sf::Texture& texture)
: SceneNode(context)
, mBackground(size)
, mText()
, mHintText()
, mHintString()
, mString()
, mMarginVertical(0.f)
, mMarginHorizontal(0.f)
, mAlignment(Alignment(Top | Left))
, mIsFocused(false)
, mCursor(sf::Vector2f(mCursorWidth, 0.f))
, mCursorTime(sf::Time::Zero)
, mCursorVisible(false)
{
    mHintText.setColor(sf::Color(0xC1C1C1FF));
    mText.setColor(sf::Color::Black);
    fixTextsPosition();
    mBackground.setTexture(&texture);
    mCursor.setFillColor(sf::Color::Black);
    putText();

    setListeners();
}

sf::FloatRect SearchbarNode::getLocalBounds() const
{
    return mBackground.getLocalBounds();
}

void SearchbarNode::setMarginVertical(float margin)
{
    mMarginVertical = margin;
    fixTextsPosition();
    putText();
}

void SearchbarNode::setMarginHorizontal(float margin)
{
    mMarginHorizontal = margin;
    fixTextsPosition();
}

void SearchbarNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mBackground, states);

    states.transform *= mBackground.getTransform();

    if(mString.size() > 0) {
        target.draw(mText, states);
    }
    else
        target.draw(mHintText, states);

    
    if(mCursorVisible && isFocused())
        target.draw(mCursor, states);
}

void SearchbarNode::fixTextsPosition()
{
    sf::Vector2f textOrigin;
    sf::Vector2f hintTextOrigin;

    sf::Vector2f textPosition;
    sf::Vector2f hintTextPosition;

    sf::Vector2f backgroundSize = mBackground.getSize();

    if(mAlignment & Left)
    {
        textOrigin.x = mText.getLocalBounds().left;
        hintTextOrigin.x = mHintText.getLocalBounds().left;

        textPosition.x = mMarginHorizontal;
        hintTextPosition.x = mMarginHorizontal;
    }
    else if(mAlignment & Middle)
    {
        textOrigin.x = mText.getLocalBounds().left + mText.getLocalBounds().width / 2.f;
        hintTextOrigin.x = mHintText.getLocalBounds().left + mHintText.getLocalBounds().width / 2.f;

        textPosition.x = backgroundSize.x / 2.f;
        hintTextPosition.x = backgroundSize.x / 2.f;
    }
    else if(mAlignment & Right)
    {
        textOrigin.x = mText.getLocalBounds().left + mText.getLocalBounds().width;
        hintTextOrigin.x = mHintText.getLocalBounds().left + mHintText.getLocalBounds().width;

        textPosition.x = backgroundSize.x - mMarginHorizontal;
        hintTextPosition.x = backgroundSize.x - mMarginHorizontal;
    }
    if(mAlignment & Top)
    {
        textOrigin.y = mText.getLocalBounds().top;
        hintTextOrigin.y = mHintText.getLocalBounds().top;

        textPosition.y = mMarginVertical;
        hintTextPosition.y = mMarginVertical;
    }
    else if(mAlignment & Center)
    {
        textOrigin.y = mText.getLocalBounds().top + mText.getLocalBounds().height / 2.f;
        hintTextOrigin.y = mHintText.getLocalBounds().top + mHintText.getLocalBounds().height / 2.f;

        textPosition.y = backgroundSize.y / 2.f;
        hintTextPosition.y = backgroundSize.y / 2.f;
    }
    else if(mAlignment & Bottom)
    {
        textOrigin.y = mText.getLocalBounds().top + mText.getLocalBounds().height;
        hintTextOrigin.y = mHintText.getLocalBounds().top + mHintText.getLocalBounds().height;

        textPosition.y = backgroundSize.y - mMarginVertical;
        hintTextPosition.y = backgroundSize.y - mMarginVertical;
    }
    textOrigin = hintTextOrigin;

    mText.setOrigin(textOrigin);
    mHintText.setOrigin(hintTextOrigin);

    mText.setPosition(textPosition);
    mHintText.setPosition(hintTextPosition);
    putText();
}

void SearchbarNode::setListeners()
{
    setOnClick([this](SceneNode& node)
    {
        mIsFocused = true;
    });

    setOnClickAway([this](SceneNode& node)
    {
        mIsFocused = false;
    });
}

void SearchbarNode::handleEventCurrent(const sf::Event& event, int& command)
{
    SceneNode::handleEventCurrent(event, command);

    if(isFocused())
    {
        if(event.type == sf::Event::TextEntered)
        {
            if(event.text.unicode == 8) // Backspace
            {
                if(mString.size() > 0)
                    mString.pop_back();
            }
            else if(event.text.unicode == 13) // Enter
            {
                if(mOnEnter)
                    mOnEnter(*this);
            }
            else if(event.text.unicode == 127) // Ctrl + Backspace
            {
                mString.clear();
            }
            else
            {
                sf::Text text(mString + std::string(1, event.text.unicode), *mText.getFont(), mText.getCharacterSize());
                if(text.getLocalBounds().width <= mBackground.getSize().x - mMarginHorizontal * 2.f)
                    mString += event.text.unicode;
            }
            putText();
        }
    }
}

bool SearchbarNode::isFocused() const
{
    return mIsFocused;
}

void SearchbarNode::putText()
{
    mText.setString(mString);

    mCursor.setPosition(sf::Vector2f(
        mText.findCharacterPos(mString.size()).x,
        mText.getCharacterSize() * 0.3f
    ));
}

void SearchbarNode::setOnEnter(std::function<void(SceneNode&)> onEnter)
{
    mOnEnter = onEnter;
}

void SearchbarNode::setAlignment(Alignment alignment)
{
    mAlignment = alignment;
    fixTextsPosition();
}

void SearchbarNode::setHint(const std::string& hint)
{
    mHintString = hint;
    mHintText.setString(mHintString);
}

void SearchbarNode::setCharacterSize(unsigned int size)
{
    mText.setCharacterSize(size);
    mHintText.setCharacterSize(size);
    mCursor.setSize(sf::Vector2f(mCursorWidth, size * 0.8f));
    fixTextsPosition();
}

void SearchbarNode::setFont(const sf::Font& font)
{
    mText.setFont(font);
    mHintText.setFont(font);
    fixTextsPosition();
}

void SearchbarNode::updateCurrent(sf::Time dt)
{
    SceneNode::updateCurrent(dt);

    mCursorTime += dt;
    if(mCursorTime >= mCursorBlinkTime) {
        mCursorTime = sf::Time::Zero;
        mCursorVisible = !mCursorVisible;
    }
}

std::string SearchbarNode::getString() const
{
    return mString;
}

void SearchbarNode::clear()
{
    mString.clear();
    putText();
}