#include <iostream>
#include <Activity/ActivityGameOver.hpp>

ActivityGameOver::ActivityGameOver(ActivityStack& stack, Context context, Intent::Ptr intent)
: Activity(stack, context, std::move(intent))
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();

    mScore = getIntent()->getExtra<int>("score");
    mWrongAnswers = getIntent()->getExtra<std::vector<std::string>>("wrongAnswers");
    mTime = getIntent()->getExtra<sf::Time>("totalTime");
}

void ActivityGameOver::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode(&getContext()));
        mSceneLayers[i] = layer.get();
        mSceneGraph->attachChild(std::move(layer));
    }

    // Background layer
    SceneNode::Ptr background(new RectangleNode(
        &getContext(), 
        sf::Vector2f(1000.f, 800.f),
        sf::Color(0x606060FF)
    ));
    SceneNode::Ptr background2(new RectangleNode(
        &getContext(), 
        sf::Vector2f(975.f, 775.f),
        getContext().textures->get(Textures::GameOverBackground)
    ));
    background2->setPosition(13.f, 12.f);
    mSceneLayers[Background]->attachChild(std::move(background));
    mSceneLayers[Background]->attachChild(std::move(background2));
}

void ActivityGameOver::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityGameOver::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityGameOver::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);
    return false;
}

bool ActivityGameOver::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}