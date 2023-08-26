#include <Activity/ActivityFavoriteList.hpp>
#include <iostream>

ActivityFavoriteList::ActivityFavoriteList(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

void ActivityFavoriteList::buildScene()
{
    SceneNode::Ptr dimBackground(new RectangleNode(
        &getContext(),
        sf::Vector2f(getContext().window->getSize().x, getContext().window->getSize().y), 
        sf::Color(0x0000007F)
    ));

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

    background2->attachChild(std::move(title));
    mSceneGraph->attachChild(std::move(dimBackground));
    mSceneGraph->attachChild(std::move(background1));
    mSceneGraph->attachChild(std::move(background2));
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