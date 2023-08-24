#include <iostream>
#include <Activity/ActivityCredit.hpp>

ActivityCredit::ActivityCredit(ActivityStack& stack, Context context, Intent::Ptr intent)
: Activity(stack, context, std::move(intent))
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

void ActivityCredit::buildScene()
{
    SceneNode::Ptr node(new SceneNode(&getContext()));
    mSceneLayers[Background] = node.get();
    mSceneGraph->attachChild(std::move(node));

    // Background layer
    SceneNode::Ptr dim(new RectangleNode(
        &getContext(), 
        sf::Vector2f(getContext().window->getSize().x, getContext().window->getSize().y),
        sf::Color(0x0000007F)
    ));
    dim->setOnClick([this](SceneNode& node) {
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

    SceneNode::Ptr node2(new SceneNode(&getContext()));
    mSceneLayers[Title] = node2.get();
    background2->attachChild(std::move(node2));

    SceneNode::Ptr node3(new SceneNode(&getContext()));
    mSceneLayers[Names] = node3.get();
    node3->setPosition(0.f, 154.f);
    background2->attachChild(std::move(node3));

    mSceneLayers[Background]->attachChild(std::move(dim));
    mSceneLayers[Background]->attachChild(std::move(background1));
    mSceneLayers[Background]->attachChild(std::move(background2));

    // Title layer
    SceneNode::Ptr title(
        new TextNode(&getContext(), 
        "Credits", 
        getContext().fonts->get(Fonts::DEFAULT), 
        65,
        sf::Color(0xFFFFFFFF)));
    
    sf::FloatRect bounds = title->getLocalBounds();
    title->setOrigin(bounds.left + bounds.width/2.f, bounds.top);
    title->setPosition(
        725.f / 2.f,
        30.f
    );

    mSceneLayers[Title]->attachChild(std::move(title));

    //Names layer
    std::string names[] = {
        "Toan Vong",
        "Toan Vong",
        "Toan Vong",
        "Toan Vong"
    };

    std::string roles[] = {
        "Project Manager",
        "Lead Programmer",
        "Lead Designer",
        "Lead Artist"
    };

    SceneNode::Ptr name[4];
    SceneNode::Ptr role[4];

    float off_height = 0.f;

    for(int i = 0; i < 4; i++)
    {
        name[i] = SceneNode::Ptr(
            new TextNode(&getContext(), 
            names[i], 
            getContext().fonts->get(Fonts::DEFAULT), 
            48,
            sf::Color(0xFFFFFFFF)));
        name[i]->setPosition(106.f, 0.f);

        role[i] = SceneNode::Ptr(
            new TextNode(&getContext(), 
            roles[i], 
            getContext().fonts->get(Fonts::DEFAULT), 
            48,
            sf::Color(0xFFFFFFFF)));
        role[i]->setOrigin(role[i]->getLocalBounds().width, 0);
        role[i]->setPosition(725.f - 106.f, 0.f);

        float height = std::max(
            name[i]->getLocalBounds().height,
            role[i]->getLocalBounds().height
        );

        name[i]->move(0.f, off_height);
        role[i]->move(0.f, off_height);

        off_height += height + 60.f;

        mSceneLayers[Names]->attachChild(std::move(name[i]));
        mSceneLayers[Names]->attachChild(std::move(role[i]));
    }
}

void ActivityCredit::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityCredit::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityCredit::handleEvent(const sf::Event& event)
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

bool ActivityCredit::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}