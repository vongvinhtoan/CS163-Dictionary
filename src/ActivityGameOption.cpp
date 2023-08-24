#include <iostream>
#include <Activity/ActivityGameOption.hpp>

ActivityGameOption::ActivityGameOption(ActivityStack& stack, Context context, Intent::Ptr intent)
: Activity(stack, context, std::move(intent))
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

void ActivityGameOption::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        if(i == Logo || i == Button)
            continue;
        SceneNode::Ptr layer(new SceneNode(&getContext()));
        mSceneLayers[i] = layer.get();
        mSceneGraph->attachChild(std::move(layer));
    }

    // Background layer
    SceneNode::Ptr background(new RectangleNode(&getContext(), sf::Vector2f(1000.f, 793.f), sf::Color(0xF4CBEDFF)));
    
    mSceneLayers[Background]->attachChild(std::move(background));

    // Dashboard background layer
    SceneNode::Ptr startingFrameBackground(
        new RectangleNode(&getContext(), sf::Vector2f(300.f, 793.f),
        getContext().textures->get(Textures::StartingFrameBackground)));
    startingFrameBackground->setPosition(350.f, 0.f);

    mSceneLayers[DashboardBackground]->attachChild(std::move(startingFrameBackground));

    SceneNode::Ptr menu(
        new RectangleNode(&getContext(), sf::Vector2f(200.f, 793.f),
        getContext().textures->get(Textures::MenuBackground)));
    menu->setPosition(400.f, 0.f);
    SceneNode::Ptr logoLayer(new SceneNode(&getContext()));
    SceneNode::Ptr buttonLayer(new SceneNode(&getContext()));
    logoLayer->setPosition(0.f, 78.f);
    buttonLayer->setPosition(10.f, 306.f);
    mSceneLayers[Logo] = logoLayer.get();
    mSceneLayers[Button] = buttonLayer.get();
    menu->attachChild(std::move(logoLayer));
    menu->attachChild(std::move(buttonLayer));
    mSceneLayers[DashboardBackground]->attachChild(std::move(menu));

    // Logo layer
    SceneNode::Ptr logo(
        new RectangleNode(&getContext(), sf::Vector2f(200.f, 193.f),
        getContext().textures->get(Textures::Logo)));

    SceneNode::Ptr name(
        new TextNode(&getContext(), 
        "Dictionary", 
        getContext().fonts->get(Fonts::DEFAULT), 
        50,
        sf::Color(0xFFFFFFFF)));

    ((TextNode*)name.get())->alignCenter();
    name->move(logo->getLocalBounds().width / 2.f, logo->getLocalBounds().height / 2.f);
    float offset = 3;
    name->move(-offset, -offset * 3.73205080757);
    name->rotate(-15);

    logo->attachChild(std::move(name));
    mSceneLayers[Logo]->attachChild(std::move(logo));

    // Button layer
    SceneNode::Ptr wordButton(
        new ButtonNode(&getContext(), sf::Vector2f(180.f, 40.f), "Word", 50));
    wordButton->setOnClick([this](SceneNode& node){
        ((ButtonNode*)&node)->setBackgroundColor(sf::Color(0xA02C2CFF));
        requestStackPop();
        requestStackPush(Activities::GAMEWORD);
    });

    SceneNode::Ptr definitionButton(
        new ButtonNode(&getContext(), sf::Vector2f(180.f, 40.f), "Definition", 50));
    definitionButton->setPosition(0, 35 + 40);
    definitionButton->setOnClick([this](SceneNode& node){
        ((ButtonNode*)&node)->setBackgroundColor(sf::Color(0xA02C2CFF));
        requestStackPop();
        requestStackPush(Activities::GAMEDEFINITION);
    });
    
    SceneNode::Ptr backButton(
        new ButtonNode(&getContext(), sf::Vector2f(180.f, 40.f), "Back", 50));
    backButton->setPosition(0, 35 + 40);
    backButton->setOnClick([this](SceneNode& node){
        ((ButtonNode*)&node)->setBackgroundColor(sf::Color(0xA02C2CFF));
        requestStackPop();
    });

    definitionButton->attachChild(std::move(backButton));
    wordButton->attachChild(std::move(definitionButton));

    mSceneLayers[Button]->attachChild(std::move(wordButton));

    // Footer layer
    SceneNode::Ptr footer(
        new RectangleNode(&getContext(), sf::Vector2f(1000.f, 29.f),
        getContext().textures->get(Textures::Footer)));
    footer->setPosition(0.f, 772.f);

    SceneNode::Ptr versionText(
        new TextNode(&getContext(), 
        "Version: Alpha 1.0.0", 
        getContext().fonts->get(Fonts::DEFAULT), 
        30,
        sf::Color(0x000000FF)));
    versionText->setPosition(-versionText->getLocalBounds().left + 4, -versionText->getLocalBounds().top + 4);

    SceneNode::Ptr updateText(
        new TextNode(&getContext(), 
        "Update: 20/08/2023", 
        getContext().fonts->get(Fonts::DEFAULT), 
        30,
        sf::Color(0x000000FF)));
    updateText->setPosition(footer->getLocalBounds().width - updateText->getLocalBounds().width - 4, -updateText->getLocalBounds().top + 4);

    footer->attachChild(std::move(versionText));
    footer->attachChild(std::move(updateText));

    mSceneLayers[Footer]->attachChild(std::move(footer));
}

void ActivityGameOption::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityGameOption::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityGameOption::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);
    return false;
}

bool ActivityGameOption::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}