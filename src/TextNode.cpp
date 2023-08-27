#include <SceneNode/TextNode.hpp>
#include <iostream>

TextNode::TextNode(Activity::Context* context)
: SceneNode(context)
, sf::Text()
, width(-1)
, height(-1)
{
}

TextNode::TextNode(Activity::Context* context, const std::string& text)
: SceneNode(context)
, sf::Text("", context->fonts->get(Fonts::DEFAULT), 30)
, width(-1)
, height(-1)
{
    setString(text);
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font)
: SceneNode(context)
, sf::Text("", font, 30)
, width(-1)
, height(-1)
{
    setString(text);
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize)
: SceneNode(context)
, sf::Text("", font, characterSize)
, width(-1)
, height(-1)
{
    setString(text);
}

TextNode::TextNode(Activity::Context* context, const std::string& text, const sf::Font& font, unsigned int characterSize, const sf::Color& color)
: SceneNode(context)
, sf::Text("", font, characterSize)
, width(-1)
, height(-1)
{
    setColor(color);
    setString(text);
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

void TextNode::setString(const std::string& text)
{
    std::vector<std::string> words;
    // Split the string into words
    std::string word;
    for (auto& c : text)
    {
        if (c == ' ' || c == '\n')
        {
            if(!word.empty()) words.push_back(word);
            word.clear();
        }
        else
        {
            word += c;
        }
    }
    if(!word.empty()) words.push_back(word);

    std::string line;
    sf::Text lineText("", *getFont(), getCharacterSize());
    for (auto& word : words)
    {
        lineText.setString(line + word + " ");
        if (width != -1 && lineText.getLocalBounds().width > width)
        {
            lineText.setString(line + "\n" + word + " ");
            if(height != -1 &&lineText.getLocalBounds().height > height) break;
            line += "\n" + word + " ";
        }
        else
        {
            line += word + " ";
        }
    }
    if(line.back() == ' ') line.pop_back();

    Text::setString(line);
}

void TextNode::setWidth(int width)
{
    this->width = width;
    setString(getString());
}

void TextNode::setHeight(int height)
{
    this->height = height;
    setString(getString());
}

int TextNode::getWidth()
{
    return this->width;
}

int TextNode::getHeight()
{
    return this->height;
}