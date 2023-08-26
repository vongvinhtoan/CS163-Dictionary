#include <SceneNode/SearchbarNode.hpp>

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
{
    fixTextsPosition();
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
{
    fixTextsPosition();
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
{
    fixTextsPosition();
    mBackground.setFillColor(color);
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
{
    fixTextsPosition();
    mBackground.setTexture(&texture);
}

sf::FloatRect SearchbarNode::getLocalBounds() const
{
    return mBackground.getLocalBounds();
}

void SearchbarNode::setMarginVertical(float margin)
{
    mMarginVertical = margin;
    fixTextsPosition();
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

    target.draw(mText, states);
    target.draw(mHintText, states);
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

    mText.setOrigin(textOrigin);
    mHintText.setOrigin(hintTextOrigin);

    mText.setPosition(textPosition);
    mHintText.setPosition(hintTextPosition);
}