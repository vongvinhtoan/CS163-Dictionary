#include <ActivityDashboard.hpp>

ActivityDashboard::ActivityDashboard(ActivityStack& stack, Context context)
: Activity(stack, context)
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

#include <iostream>

void ActivityDashboard::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode(&getContext()));
        mSceneLayers[i] = layer.get();
        mSceneGraph->attachChild(std::move(layer));
    }

    // Background layer
    SceneNode::Ptr background(new RectangleNode(&getContext(), sf::Vector2f(1000.f, 793.f), sf::Color(0xF4CBEDFF)));

    SceneNode::Ptr startingFrameBackground(
        new RectangleNode(&getContext(), sf::Vector2f(300.f, 793.f),
        getContext().textures->get(Textures::StartingFrameBackground)));
    startingFrameBackground->setPosition(350.f, 0.f);
    
    SceneNode::Ptr menu(
        new RectangleNode(&getContext(), sf::Vector2f(200.f, 793.f),
        getContext().textures->get(Textures::MenuBackground)));
    menu->setPosition(400.f, 0.f);

    SceneNode::Ptr logo(
        new RectangleNode(&getContext(), sf::Vector2f(200.f, 193.f),
        getContext().textures->get(Textures::Logo)));
    logo->setPosition(0.f, 78.f);
    logo->setOnClick([] (SceneNode& node) { std::cout << "Clicked on logo" << std::endl; });
    logo->setOnHover([] (SceneNode& node) { std::cout << "Hovered on logo" << std::endl; });

    menu->attachChild(std::move(logo));
    menu->setOnClick([] (SceneNode& node) { std::cout << "Clicked on menu" << std::endl; });
    menu->setOnHover([] (SceneNode& node) { std::cout << "Hovered on menu" << std::endl; });

    SceneNode::Ptr footer(
        new RectangleNode(&getContext(), sf::Vector2f(1000.f, 29.f),
        getContext().textures->get(Textures::Footer)));
    footer->setPosition(0.f, 772.f);
    
    mSceneLayers[Background]->attachChild(std::move(background));
    mSceneLayers[Background]->attachChild(std::move(startingFrameBackground));
    mSceneLayers[Background]->attachChild(std::move(menu));
    mSceneLayers[Background]->attachChild(std::move(footer));
}

void ActivityDashboard::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityDashboard::update(sf::Time dt)
{
    return true;
}

bool ActivityDashboard::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);
    return true;
}

bool ActivityDashboard::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return true;
}