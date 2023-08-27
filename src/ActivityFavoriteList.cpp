#include <Activity/ActivityFavoriteList.hpp>
#include <iostream>

ActivityFavoriteList::ActivityFavoriteList(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
, mPagerIndex(0)
{
    buildScene();

    std::vector<std::string> favorites = getContext().api->get_favorites();
    buildFavorites(favorites);
    setPagerIndex(0);
}

void ActivityFavoriteList::buildScene()
{
    SceneNode::Ptr dimBackground(new RectangleNode(
        &getContext(),
        sf::Vector2f(getContext().window->getSize().x, getContext().window->getSize().y), 
        sf::Color(0x0000007F)
    ));
    dimBackground->setOnClick([this](SceneNode& node) {
        requestStackPop();
    });

    SceneNode::Ptr background1(new RectangleNode(
        &getContext(), 
        sf::Vector2f(750.f, 650.f),
        getContext().textures->get(Textures::WoodenBackground1)
    ));
    background1->setPosition(
        (getContext().window->getSize().x / 2) - (background1->getLocalBounds().width / 2),
        (getContext().window->getSize().y / 2) - (background1->getLocalBounds().height / 2)
    );

    SceneNode::Ptr background2(new RectangleNode(
        &getContext(), 
        sf::Vector2f(725.f, 625.f),
        getContext().textures->get(Textures::WoodenBackground2)
    ));
    background2->setPosition(
        (getContext().window->getSize().x / 2) - (background2->getLocalBounds().width / 2),
        (getContext().window->getSize().y / 2) - (background2->getLocalBounds().height / 2)
    );
    
    SceneNode::Ptr title(
        new TextNode(&getContext(), 
        "Favorite list", 
        getContext().fonts->get(Fonts::DEFAULT), 
        90,
        sf::Color(0xFF0000FF)));
    
    sf::FloatRect bounds = title->getLocalBounds();
    title->setOrigin(bounds.left + bounds.width/2.f, bounds.top);
    title->setPosition(
        725.f / 2.f,
        30.f
    );

    SceneNode::Ptr favoriteFrame(
        new RectangleNode(
        &getContext(), 
        sf::Vector2f(719.f, 396.f),
        getContext().textures->get(Textures::FavoriteFrame)
    ));
    favoriteFrame->setPosition(
        3.f,
        161.f
    );

    const float margin = 30.f;

    SceneNode::Ptr favoriteHoder(new RectangleNode(
        &getContext(), 
        sf::Vector2f(719.f - (margin * 2), 396.f - (margin * 2)),
        sf::Color(0x00000000)
    ));
    favoriteHoder->setPosition(
        3.f + margin,
        161.f + margin
    );
    mFavoriteHolder = favoriteHoder.get();

    SceneNode::Ptr pageIndicator(
        new TextNode(&getContext(), 
        "1/1", 
        getContext().fonts->get(Fonts::DEFAULT), 
        55,
        sf::Color(0xFFFFFFFF)
    ));
    mPageIndicator = (TextNode*)pageIndicator.get();

    SceneNode::Ptr prevButton(
        new TextNode(&getContext(), 
        "<", 
        getContext().fonts->get(Fonts::DEFAULT), 
        55,
        sf::Color(0xFFFFFFFF)
    ));
    mPrevButton = (TextNode*)prevButton.get();
    buttonize(prevButton.get());
    mPrevButton->setOnClick([this](SceneNode& node) {
        prevPage();
        fixPageIndicator();
    });

    SceneNode::Ptr nextButton(
        new TextNode(&getContext(), 
        ">", 
        getContext().fonts->get(Fonts::DEFAULT), 
        55,
        sf::Color(0xFFFFFFFF)
    ));
    mNextButton = (TextNode*)nextButton.get();
    buttonize(nextButton.get());
    mNextButton->setOnClick([this](SceneNode& node) {
        nextPage();
        fixPageIndicator();
    });

    background2->attachChild(std::move(title));
    background2->attachChild(std::move(favoriteFrame));
    background2->attachChild(std::move(favoriteHoder));
    background2->attachChild(std::move(pageIndicator));
    background2->attachChild(std::move(prevButton));
    background2->attachChild(std::move(nextButton));
    mSceneGraph->attachChild(std::move(dimBackground));
    mSceneGraph->attachChild(std::move(background1));
    mSceneGraph->attachChild(std::move(background2));
    fixPageIndicator();
}

void ActivityFavoriteList::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityFavoriteList::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityFavoriteList::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            requestStackPop();
        }
    }

    return false;
}

bool ActivityFavoriteList::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}

void ActivityFavoriteList::buttonize(SceneNode* node)
{
    node->setOnLostHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
    });
    node->setOnHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
    });
}

void ActivityFavoriteList::buildFavorites(const std::vector<std::string>& favorites)
{
    const float margin = 30.f;
    const float width = 719.f - (margin * 2);
    const float height = 416.f - (margin * 2);
    const float item_height = 50.f;
    const float item_width = width - (margin * 2);
    const float item_margin = 10.f;

    for (int i = 0; i < favorites.size(); i++)
    {
        SceneNode::Ptr favorite(new TextNode(
            &getContext(),
            favorites[i],
            getContext().fonts->get(Fonts::DEFAULT),
            40,
            sf::Color(0xFFFFFFFF)
        ));
        mFavorites.push_back(favorite.get());
        favorite->disable();
        buttonize(favorite.get());
        favorite->setOnClick([this, i](SceneNode& node) {
            Intent::Ptr intent(new Intent());
            intent->putExtra("word", ((TextNode*)&node)->getString().toAnsiString());
            requestStackPop();
            requestBackActivity(std::move(intent));
        });
        mFavoriteHolder->attachChild(std::move(favorite));

        fixPosition(i);
    }
}

void ActivityFavoriteList::fixPosition(int index)
{
    const float margin = 30.f;
    const float width = 719.f - (margin * 2);
    const float height = 416.f - (margin * 2);
    const float spacing = 20.f;

    sf::Vector2f origin;
    sf::Vector2f position;

    int x = index % maxDisplay % 3;
    int y = index % maxDisplay / 3;

    if(x == 0)
    {
        origin.x = mFavorites[index]->getLocalBounds().left;
        position.x = 0.f;
    }
    else if(x == 1)
    {
        origin.x = mFavorites[index]->getLocalBounds().left + mFavorites[index]->getLocalBounds().width / 2.f;
        position.x = width / 2.f;
    }
    else if(x == 2)
    {
        origin.x = mFavorites[index]->getLocalBounds().left + mFavorites[index]->getLocalBounds().width;
        position.x = width;
    }

    origin.y = mFavorites[index]->getLocalBounds().top;
    position.y = y * ((TextNode*)mFavorites[index])->getCharacterSize() + y * spacing;

    mFavorites[index]->setOrigin(origin);
    mFavorites[index]->setPosition(position);
}

void ActivityFavoriteList::nextPage()
{
    mPagerIndex++;
    setPagerIndex(mPagerIndex);
}

void ActivityFavoriteList::prevPage()
{
    mPagerIndex--;
    setPagerIndex(mPagerIndex);
}

void ActivityFavoriteList::setPagerIndex(int index)
{
    if (index < 0)
    {
        mPagerIndex = ((int)mFavorites.size()-1) / maxDisplay;
    }
    else if (index > ((int)mFavorites.size()-1) / maxDisplay)
    {
        mPagerIndex = 0;
    }

    for (int i = 0; i < mFavorites.size(); i++)
    {
        if (i >= mPagerIndex * maxDisplay && i < (mPagerIndex + 1) * maxDisplay)
        {
            mFavorites[i]->enable();
        }
        else
        {
            mFavorites[i]->disable();
        }
    }

    fixPageIndicator();
}

void ActivityFavoriteList::fixPageIndicator()
{
    const float margin = 40.f;
    const float spacing = 20.f;

    mPageIndicator->setString(std::to_string(mPagerIndex + 1) + "/" + std::to_string(((int)mFavorites.size()-1) / maxDisplay + 1));

    mPageIndicator->SceneNode::setOrigin(
        mPageIndicator->getLocalBounds().left + mPageIndicator->getLocalBounds().width / 2.f,
        mPageIndicator->getLocalBounds().top + mPageIndicator->getLocalBounds().height / 2.f
    );
    mPageIndicator->SceneNode::setPosition(
        725.f / 2.f,
        625.f - margin
    );

    mPrevButton->SceneNode::setOrigin(
        mPrevButton->getLocalBounds().left + mPrevButton->getLocalBounds().width,
        mPrevButton->getLocalBounds().top + mPrevButton->getLocalBounds().height / 2.f
    );
    mPrevButton->SceneNode::setPosition(
        725.f / 2.f - mPageIndicator->getLocalBounds().width / 2.f - spacing,
        625.f - margin
    );

    mNextButton->SceneNode::setOrigin(
        mNextButton->getLocalBounds().left,
        mNextButton->getLocalBounds().top + mNextButton->getLocalBounds().height / 2.f
    );
    mNextButton->SceneNode::setPosition(
        725.f / 2.f + mPageIndicator->getLocalBounds().width / 2.f + spacing,
        625.f - margin
    );
}