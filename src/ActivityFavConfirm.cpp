#include <iostream>
#include <Activity/ActivityFavConfirm.hpp>

ActivityFavConfirm::ActivityFavConfirm(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

void ActivityFavConfirm::buildScene()
{
    // Background layer
    SceneNode::Ptr dim(new RectangleNode(
        &getContext(), 
        sf::Vector2f(getContext().window->getSize().x, getContext().window->getSize().y),
        sf::Color(0x0000007F)
    ));
    SceneNode::Ptr background1(new RectangleNode(
        &getContext(), 
        sf::Vector2f(827.f, 410.f),
        getContext().textures->get(Textures::ConfirmBackground1)
    ));
    background1->setPosition(
        (getContext().window->getSize().x / 2) - (background1->getLocalBounds().width / 2),
        (getContext().window->getSize().y / 2) - (background1->getLocalBounds().height / 2)
    );

    SceneNode::Ptr background2(new RectangleNode(
        &getContext(), 
        sf::Vector2f(800.f, 382.f),
        getContext().textures->get(Textures::ConfirmBackground2)
    ));
    background2->setPosition(
        (getContext().window->getSize().x / 2) - (background2->getLocalBounds().width / 2),
        (getContext().window->getSize().y / 2) - (background2->getLocalBounds().height / 2)
    );

    SceneNode::Ptr title(new TextNode(
        &getContext(), 
        "Confirm?", 
        getContext().fonts->get(Fonts::DEFAULT),
        128, 
        sf::Color(0xF5F07CFF)
    ));
    title->setOrigin(
        title->getLocalBounds().left + title->getLocalBounds().width / 2.f,
        title->getLocalBounds().top
    );
    title->setPosition(
        background2->getLocalBounds().width / 2.f,
        37.f
    );

    SceneNode::Ptr yesButton(new ButtonNode(
        &getContext(), 
        sf::Vector2f(350.f, 88.9f),
        "Yes",
        50
    ));
    yesButton->setOrigin(0.f, 0.f);
    yesButton->setPosition(
        28.f,
        229.f
    );
    yesButton->setOnClick([this](SceneNode& node){
        Intent::Ptr intent(new Intent());
        intent->putExtra("confirmed", true);
        requestStackPop();
        requestBackActivity(std::move(intent));
    });

    SceneNode::Ptr noButton(new ButtonNode(
        &getContext(), 
        sf::Vector2f(350.f, 88.9f),
        "No",
        50
    ));
    noButton->setOrigin(noButton->getLocalBounds().width, 0.f);
    noButton->setPosition(
        background2->getLocalBounds().width - 28.f,
        229.f
    );
    noButton->setOnClick([this](SceneNode& node){
        Intent::Ptr intent(new Intent());
        intent->putExtra("confirmed", false);
        requestStackPop();
        requestBackActivity(std::move(intent));
    });

    background2->attachChild(std::move(title));
    background2->attachChild(std::move(yesButton));
    background2->attachChild(std::move(noButton));
    mSceneGraph->attachChild(std::move(dim));
    mSceneGraph->attachChild(std::move(background1));
    mSceneGraph->attachChild(std::move(background2));
}

void ActivityFavConfirm::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityFavConfirm::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityFavConfirm::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);

    return false;
}

bool ActivityFavConfirm::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}