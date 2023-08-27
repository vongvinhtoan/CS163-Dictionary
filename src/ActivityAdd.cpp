#include <Activity/ActivityAdd.hpp>
#include <iostream>

ActivityAdd::ActivityAdd(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
{
    buildScene();
}

void ActivityAdd::buildScene()
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
    
    SceneNode::Ptr title(new TextNode(
        &getContext(), 
        "Add new word", 
        getContext().fonts->get(Fonts::DEFAULT), 
        90,
        sf::Color(0xFFFFFFFF)
    ));
    
    sf::FloatRect bounds = title->getLocalBounds();
    title->setOrigin(bounds.left + bounds.width/2.f, bounds.top);
    title->setPosition(
        725.f / 2.f,
        26.f
    );

    SceneNode::Ptr addWordBar(new SearchbarNode(
        &getContext(),
        sf::Vector2f(551.f, 75.f),
        getContext().textures->get(Textures::AddWordBar)
    ));
    mAddWordBar = static_cast<SearchbarNode*>(addWordBar.get());
    mAddWordBar->setAlignment(SearchbarNode::Alignment(
        SearchbarNode::Alignment::Left | SearchbarNode::Alignment::Center
    ));
    mAddWordBar->setPosition(153.f, 126.f);
    mAddWordBar->setCharacterSize(50);
    mAddWordBar->setFont(getContext().fonts->get(Fonts::DEFAULT));
    mAddWordBar->setHint("New word here");
    mAddWordBar->setMarginHorizontal(22.f);
    mAddWordBar->setOnEnter([this](SceneNode& node) {
        std::cout << "Enter pressed" << std::endl;
        mAddDefBar->setFocus(true);
        mAddWordBar->setFocus(false);
    });

    SceneNode::Ptr addDefBar(new SearchbarNode(
        &getContext(),
        sf::Vector2f(721.f, 217.f),
        getContext().textures->get(Textures::AddDefBar)
    ));
    mAddDefBar = static_cast<SearchbarNode*>(addDefBar.get());
    mAddDefBar->setAlignment(SearchbarNode::Alignment(
        SearchbarNode::Alignment::Left | SearchbarNode::Alignment::Top
    ));
    mAddDefBar->setPosition(2.f, 406.f);
    mAddDefBar->setCharacterSize(50);
    mAddDefBar->setFont(getContext().fonts->get(Fonts::DEFAULT));
    mAddDefBar->setHint("New definition here");
    mAddDefBar->setMarginHorizontal(22.f);
    mAddDefBar->setMarginVertical(12.f);
    mAddDefBar->setOnEnter([this](SceneNode& node) {
        std::cout << "Enter pressed" << std::endl;
        std::string word = mAddWordBar->getString();
        std::string def = mAddDefBar->getString();
        if(word.empty() || def.empty())
            return;
        getContext().api->add_definition(word, def);

        Intent::Ptr intent(new Intent());
        intent->putExtra("word", word);
        requestStackPop();
        requestBackActivity(std::move(intent));
    });

    background2->attachChild(std::move(title));
    background2->attachChild(std::move(addWordBar));
    background2->attachChild(std::move(addDefBar));
    mSceneGraph->attachChild(std::move(dimBackground));
    mSceneGraph->attachChild(std::move(background1));
    mSceneGraph->attachChild(std::move(background2));
}

void ActivityAdd::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityAdd::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityAdd::handleEvent(const sf::Event& event)
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

bool ActivityAdd::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}