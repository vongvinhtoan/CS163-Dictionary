#include <iostream>
#include <Activity/ActivityEditDefinition.hpp>

ActivityEditDefinition::ActivityEditDefinition(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
{
    word = getIntent()->getExtra<std::string>("word");
    definition = getIntent()->getExtra<std::string>("definition");
    definitionId = getIntent()->getExtra<int>("definitionId");
 
    buildScene(); 
}

void ActivityEditDefinition::buildScene()
{
    SceneNode::Ptr dim(new RectangleNode(
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

    SceneNode::Ptr title(new TextNode(
        &getContext(), 
        "Edit definition", 
        getContext().fonts->get(Fonts::DEFAULT),
        100, 
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

    SceneNode::Ptr editButton(new ButtonNode(
        &getContext(), 
        sf::Vector2f(250.f, 78.f),
        "Edit",
        50
    ));
    editButton->setOrigin(0.f, 0.f);
    editButton->setPosition(
        40.f,
        background2->getLocalBounds().height - 28.f - editButton->getLocalBounds().height
    );
    editButton->setOnClick([this](SceneNode& node){
        if(searchbar->getString().empty()) return;
        getContext().api->edit_definition(word, definitionId, searchbar->getString()); 

        Intent::Ptr intent(new Intent());
        intent->putExtra("word", word);
        requestStackPop();
        requestBackActivity(std::move(intent));
    });

    SceneNode::Ptr cancelButton(new ButtonNode(
        &getContext(), 
        sf::Vector2f(250.f, 78.f),
        "Cancel",
        50
    ));
    cancelButton->setOrigin(cancelButton->getLocalBounds().width, 0.f);
    cancelButton->setPosition(
        background2->getLocalBounds().width - 40.f,
        background2->getLocalBounds().height - 28.f - cancelButton->getLocalBounds().height
    );
    cancelButton->setOnClick([this](SceneNode& node){
        requestStackPop();
    });

    SceneNode::Ptr oldWordAndDefinition(new TextNode(
        &getContext(), 
        word + " - " + definition, 
        getContext().fonts->get(Fonts::DEFAULT),
        40, 
        sf::Color(0xFFFFFFFF)
    ));
    oldWordAndDefinition->setOrigin(
        oldWordAndDefinition->getLocalBounds().left,
        oldWordAndDefinition->getLocalBounds().top
    );
    oldWordAndDefinition->setPosition(
        28.f,
        120.f
    );
    ((TextNode*)oldWordAndDefinition.get())->setWidth(725.f - 28.f - 28.f);
    ((TextNode*)oldWordAndDefinition.get())->setHeight(625.f - 150.f - 28.f - 88.9f - 28.f - 28.f);

    std::unique_ptr<SearchbarNode> newDefinitionBar(new SearchbarNode(
        &getContext(), 
        sf::Vector2f(
            725.f - 28.f - 28.f, 
            background2->getLocalBounds().height - oldWordAndDefinition->getLocalBounds().height - 28.f - 88.9f - 28.f - 28.f - 28.f - 100.f),
        getContext().textures->get(Textures::AddDefBar)
    ));
    newDefinitionBar->setPosition(
        28.f,
        150.f + ((TextNode*)oldWordAndDefinition.get())->getLocalBounds().height + 28.f
    );
    newDefinitionBar->setAlignment(SearchbarNode::Alignment(
        SearchbarNode::Alignment::Left |
        SearchbarNode::Alignment::Top
    ));
    newDefinitionBar->setCharacterSize(40);
    newDefinitionBar->setHint("New definition");
    newDefinitionBar->setFont(getContext().fonts->get(Fonts::DEFAULT));
    newDefinitionBar->setOnEnter([this](SceneNode& node){
        ((SearchbarNode*)&node)->setFocus(false);
    });
    newDefinitionBar->setMarginHorizontal(22.f);
    newDefinitionBar->setMarginVertical(22.f);
    searchbar = newDefinitionBar.get();

    background2->attachChild(std::move(title));
    background2->attachChild(std::move(editButton));
    background2->attachChild(std::move(cancelButton));
    background2->attachChild(std::move(oldWordAndDefinition));
    background2->attachChild(std::move(newDefinitionBar));
    mSceneGraph->attachChild(std::move(dim));
    mSceneGraph->attachChild(std::move(background1));
    mSceneGraph->attachChild(std::move(background2));
}

void ActivityEditDefinition::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityEditDefinition::update(sf::Time dt)
{
    mSceneGraph->update(dt);
    return false;
}

bool ActivityEditDefinition::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);

    return false;
}

bool ActivityEditDefinition::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}