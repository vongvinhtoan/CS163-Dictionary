#include <iostream>
#include <Activity/ActivityDictionary.hpp>

ActivityDictionary::ActivityDictionary(ActivityStack& stack, Context context, Intent::Ptr intent)
: Activity(stack, context, std::move(intent))
, mSceneGraph(new SceneNode(&getContext()))
, mDictionaryId(Database::DictionaryId::VIET_ENG)
, mIsFavorite(false)
, mPagerIndex(0)
{
    mDefinitions = {
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
        "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb",
        "ccccccccccccccccccccccccccccccccc",
        "ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd ddd d",
        "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee",
    };

    buildScene();
}

void ActivityDictionary::buildScene()
{
    // Initialize the different layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode(&getContext()));
        mSceneLayers[i] = layer.get();
        mSceneGraph->attachChild(std::move(layer));
    }

    // Background
    {
        SceneNode::Ptr backgroundLayer(new RectangleNode(
            &getContext(),
            sf::Vector2f(getContext().window->getSize().x, 250.f),
            getContext().textures->get(Textures::DictionaryBackground)
        ));
        mSceneLayers[Background]->attachChild(std::move(backgroundLayer));

        const std::vector<std::string> dictName = {
            "VIET-ENG",
            "ENG-ENG",
            "ENG-VIET",
            "SLANG",
            "EMOJI"
        };
        const float width = 180.f;
        const float height = 40.f;
        const float spacing = 13.f;
        const float offset = getContext().window->getSize().x / 2.f - width * dictName.size() / 2.f - spacing * (dictName.size() - 1) / 2.f;
        for(int i = 0; i < dictName.size(); i++) {
            SceneNode::Ptr dictButton(new ButtonNode(
                &getContext(),
                sf::Vector2f(width, height),
                dictName[i],
                50
            ));
            dictButton->setPosition(offset + (width + spacing) * i, 177.f);
            dictButton->setOnClick([this, i] (SceneNode& node) {
                if(mDictionaryId == i) return;
                mDictionaryId = i;
            });
            mDictionaryOptionsButton[i] = dictButton.get();
            mSceneLayers[Background]->attachChild(std::move(dictButton));
        }
    }

    // Taskbar
    {
        const float spacing = 50.f;
        SceneNode::Ptr taskbar(new RectangleNode(
            &getContext(), 
            sf::Vector2f(1000.f, 50.f),
            sf::Color(0x0CBFE6FF)
        ));

        SceneNode::Ptr backTextButton(new TextNode(
            &getContext(), 
            "Back", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        backTextButton->setOnClick([this] (SceneNode& node) {
            requestStackPop();
        });
        backTextButton->setOrigin(
            backTextButton->getLocalBounds().left,
            0
        );
        backTextButton->setPosition(14.f, -7.f);

        SceneNode::Ptr tutorialTextButton(new TextNode(
            &getContext(), 
            "Tutorial", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        tutorialTextButton->setOnClick([this] (SceneNode& node) {
            // requestStackPush(Activities::Tutorial);
        });
        tutorialTextButton->setOrigin(
            tutorialTextButton->getLocalBounds().left + tutorialTextButton->getLocalBounds().width,
            0
        );
        tutorialTextButton->setPosition(1000.f - 14.f, -7.f);

        SceneNode::Ptr editTextButton(new TextNode(
            &getContext(), 
            "Edit", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        editTextButton->setOnClick([this] (SceneNode& node) {
            // requestStackPush(Activities::Edit);
        });
        editTextButton->setOrigin(
            editTextButton->getLocalBounds().left + editTextButton->getLocalBounds().width,
            0
        );
        editTextButton->setPosition(-spacing, 0);

        SceneNode::Ptr favoriteTextButton(new TextNode(
            &getContext(), 
            "Favorite", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        favoriteTextButton->setOnClick([this] (SceneNode& node) {
            // requestStackPush(Activities::Favorite);
        });
        favoriteTextButton->setOrigin(
            favoriteTextButton->getLocalBounds().left + favoriteTextButton->getLocalBounds().width,
            0
        );
        favoriteTextButton->setPosition(-spacing, 0);

        SceneNode::Ptr addTextButton(new TextNode(
            &getContext(), 
            "Add", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        addTextButton->setOrigin(
            addTextButton->getLocalBounds().left + addTextButton->getLocalBounds().width,
            0
        );
        addTextButton->setPosition(-spacing, 0);

        buttonize(backTextButton.get());
        buttonize(tutorialTextButton.get());
        buttonize(editTextButton.get());
        buttonize(favoriteTextButton.get());
        buttonize(addTextButton.get());

        mSceneLayers[Taskbar]->attachChild(std::move(taskbar));
        mSceneLayers[Taskbar]->attachChild(std::move(backTextButton));
        favoriteTextButton->attachChild(std::move(addTextButton));
        editTextButton->attachChild(std::move(favoriteTextButton));
        tutorialTextButton->attachChild(std::move(editTextButton));
        mSceneLayers[Taskbar]->attachChild(std::move(tutorialTextButton));
    }

    // Definition Background
    {
        mSceneLayers[DefinitionBackground]->setPosition(0, 250.f);
        SceneNode::Ptr definitionBackground(new RectangleNode(
            &getContext(),
            sf::Vector2f(1000.f, 550.f),
            sf::Color(0x606060FF)
        ));

        SceneNode::Ptr definitionCore(new RectangleNode(
            &getContext(),
            sf::Vector2f(975.f, 525.f),
            getContext().textures->get(Textures::DefinitionWoodenBackground)
        ));
        definitionCore->setPosition(13.f, 11.f);

        SceneNode::Ptr wordText(new TextNode(
            &getContext(), 
            "abandonnnnnn", 
            getContext().fonts->get(Fonts::DEFAULT), 
            65,
            sf::Color(0xFFFFFFFF)
        ));
        wordText->setOrigin(
            0,
            wordText->getLocalBounds().top
        );
        wordText->setPosition(39.f, 39.f);
        mWordIndicator = wordText.get();

        mFavoriteStateTexture[0] = getContext().textures->get(Textures::FavoriteStar);
        mFavoriteStateTexture[1] = getContext().textures->get(Textures::FavoriteStarFilled);

        SceneNode::Ptr favoriteStar(new RectangleNode(
            &getContext(),
            sf::Vector2f(40.f, 40.f),
            mFavoriteStateTexture[0]
        ));
        favoriteStar->setPosition(59.f + mWordIndicator->getLocalBounds().width, 44.f);
        favoriteStar->setOnClick([this] (SceneNode& node) {
            mIsFavorite = !mIsFavorite;
            ((RectangleNode*)&node)->setTexture(&mFavoriteStateTexture[mIsFavorite]);
        });
        mFavoriteIndicator = favoriteStar.get();

        SceneNode::Ptr definitionFrame(new RectangleNode(
            &getContext(),
            sf::Vector2f(944.f, 378.f),
            getContext().textures->get(Textures::DefinitionFrame)
        ));

        definitionFrame->setPosition(29.f, 109.f);


        SceneNode::Ptr definitionIdText(new TextNode(
            &getContext(), 
            std::to_string(mPagerIndex + 1) + "/" + std::to_string(mDefinitions.size()),
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        ((TextNode*)definitionIdText.get())->alignCenter();
        mDefinitionIdIndicator = definitionIdText.get();

        SceneNode::Ptr prevButton(new TextNode(
            &getContext(),
            "<",
            getContext().fonts->get(Fonts::DEFAULT),
            50,
            sf::Color(0xFFFFFFFF)
        ));
        prevButton->setOnClick([this] (SceneNode& node) {
            prevPage();
        });
        prevButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        prevButton->setOnHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
        prevButton->setOrigin(
            prevButton->getLocalBounds().left + prevButton->getLocalBounds().width,
            prevButton->getLocalBounds().top + prevButton->getLocalBounds().height / 2
        );
        mPrevButton = prevButton.get();

        SceneNode::Ptr nextButton(new TextNode(
            &getContext(),
            ">",
            getContext().fonts->get(Fonts::DEFAULT),
            50,
            sf::Color(0xFFFFFFFF)
        ));
        nextButton->setOnClick([this] (SceneNode& node) {
            nextPage();
        });
        nextButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        nextButton->setOnHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
        nextButton->setOrigin(
            nextButton->getLocalBounds().left,
            nextButton->getLocalBounds().top + nextButton->getLocalBounds().height / 2
        );
        mNextButton = nextButton.get();

        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionBackground));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionCore));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(wordText));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(favoriteStar));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionFrame));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionIdText));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(prevButton));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(nextButton));

        fixPageIndicatorPosition();
    }

    // Definition Page
    {
        mSceneLayers[DefinitionPage]->setPosition(0, 250.f);
        loadDefinitions();
    }

    // Footer
    {
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
}

void ActivityDictionary::buttonize(SceneNode* node)
{
    node->setOnLostHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
    });
    node->setOnHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
    });
}

void ActivityDictionary::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
}

bool ActivityDictionary::update(sf::Time dt)
{
    for(int i = 0; i < Database::DictionaryId::SIZE; i++) {
        mDictionaryOptionsButton[i]->setOnLostHover([this] (SceneNode& node) {
            ((ButtonNode&)node).setBackgroundColor(sf::Color(0xA02C2CFF));
        });
    }
    mDictionaryOptionsButton[mDictionaryId]->setOnLostHover([this] (SceneNode& node) {
        ((ButtonNode&)node).setBackgroundColor(sf::Color(0x5A5A5AFF));
    });

    mSceneGraph->update(dt);
    return false;
}

bool ActivityDictionary::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);
    return false;
}

bool ActivityDictionary::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}

void ActivityDictionary::fixPageIndicatorPosition()
{
    const float beyond = 23.f + 15.f;
    const float space = 20.f;
    float posHeight = 550 - beyond;
    ((TextNode*)mDefinitionIdIndicator)->alignCenter();
    mDefinitionIdIndicator->setPosition(500.f, posHeight);

    mPrevButton->setPosition(
        mDefinitionIdIndicator->getPosition().x - ((TextNode*)mDefinitionIdIndicator)->getLocalBounds().width / 2.f  - space,
        posHeight
    );

    mNextButton->setPosition(
        mDefinitionIdIndicator->getPosition().x + ((TextNode*)mDefinitionIdIndicator)->getLocalBounds().width / 2.f  + space,
        posHeight
    );
}

void ActivityDictionary::nextPage()
{
    setPagerIndex(mPagerIndex + 1);
}

void ActivityDictionary::prevPage()
{
    setPagerIndex(mPagerIndex - 1);
}

void ActivityDictionary::setPagerIndex(int index)
{
    mPages[mPagerIndex]->disable();
    mPagerIndex = index;
    if(mPagerIndex < 0) mPagerIndex = mDefinitions.size() - 1;
    if(mPagerIndex >= mDefinitions.size()) mPagerIndex = 0;

    mPages[mPagerIndex]->enable();
    ((TextNode*)mDefinitionIdIndicator)->setString(std::to_string(mPagerIndex + 1) + "/" + std::to_string(mDefinitions.size()));
    fixPageIndicatorPosition();
}

void ActivityDictionary::loadDefinitions()
{
    const float margin = 30.f;
    mPages.clear();
    mSceneLayers[DefinitionPage]->clearChildren();

    for(int i = 0; i < mDefinitions.size(); i++) {
        SceneNode::Ptr page(new TextNode(
            &getContext(), 
            mDefinitions[i], 
            getContext().fonts->get(Fonts::DEFAULT), 
            40,
            sf::Color(0xFFFFFFFF)
        ));
        ((TextNode*)page.get())->setWidth(944.f - margin * 2.f);
        ((TextNode*)page.get())->setHeight(378.f - margin * 2.f);
        page->setPosition(29.f + margin, 99.f + margin);
        page->disable();
        mPages.push_back(page.get());

        mSceneLayers[DefinitionPage]->attachChild(std::move(page));
    }
    setPagerIndex(0);
}