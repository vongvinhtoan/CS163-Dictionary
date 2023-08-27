#include <iostream>
#include <Activity/ActivityDictionary.hpp>

ActivityDictionary::ActivityDictionary(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: Activity(stack, context, std::move(intent), requestCode)
, mSceneGraph(new SceneNode(&getContext()))
, mDictionaryId(getContext().api->get_dictionary_id())
, mIsFavorite(false)
, mPagerIndex(0)
{
    buildScene();
    displayWord("");
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

        SceneNode::Ptr searchbar(new SearchbarNode(
            &getContext(),
            sf::Vector2f(420.f, 75.f),
            getContext().textures->get(Textures::DictionarySearchbar)
        ));
        searchbar->setPosition(290.f, 82.f);
        mSearchbar = (SearchbarNode*)searchbar.get();
        mSearchbar->setAlignment(SearchbarNode::Alignment(SearchbarNode::Left | SearchbarNode::Center));
        mSearchbar->setHint("Search...");
        mSearchbar->setFont(getContext().fonts->get(Fonts::DEFAULT));        
        mSearchbar->setCharacterSize(50);
        mSearchbar->setMarginHorizontal(22.f);
        mSearchbar->setOnEnter([this] (SceneNode& node) {
            SearchbarNode& searchbar = (SearchbarNode&)node;
            displayWord(searchbar.getString());
            searchbar.clear();
        });
        mSceneLayers[Background]->attachChild(std::move(searchbar));

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
                getContext().api->set_dictionary(Database::DictionaryId(i));
                displayWord("");
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

        SceneNode::Ptr favoriteTextButton(new TextNode(
            &getContext(), 
            "Favorite", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        favoriteTextButton->setOnClick([this] (SceneNode& node) {
            Intent::Ptr intent(new Intent());
            requestStackPush(Activities::FAVORITELIST, std::move(intent), FAVORITE);
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
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
        addTextButton->setOnClick([this] (SceneNode& node) {
            Intent::Ptr intent(new Intent());
            requestStackPush(Activities::ADD, std::move(intent), ADD);
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        addTextButton->setOrigin(
            addTextButton->getLocalBounds().left + addTextButton->getLocalBounds().width,
            0
        );
        addTextButton->setPosition(-spacing, 0);

        buttonize(backTextButton.get());
        buttonize(tutorialTextButton.get());
        buttonize(favoriteTextButton.get());
        buttonize(addTextButton.get());

        mSceneLayers[Taskbar]->attachChild(std::move(taskbar));
        mSceneLayers[Taskbar]->attachChild(std::move(backTextButton));
        favoriteTextButton->attachChild(std::move(addTextButton));
        tutorialTextButton->attachChild(std::move(favoriteTextButton));
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
        mWordIndicator = (TextNode*)wordText.get();

        mFavoriteStateTexture[0] = getContext().textures->get(Textures::FavoriteStar);
        mFavoriteStateTexture[1] = getContext().textures->get(Textures::FavoriteStarFilled);

        SceneNode::Ptr favoriteStar(new RectangleNode(
            &getContext(),
            sf::Vector2f(40.f, 40.f),
            mFavoriteStateTexture[0]
        ));
        favoriteStar->setPosition(59.f + mWordIndicator->getLocalBounds().width, 44.f);
        favoriteStar->setOnClick([this] (SceneNode& node) {
            requestStackPush(Activities::FAVCONFIRM, Intent::Ptr(new Intent()), FAVORITE_CONFIRM);
        });
        mFavoriteIndicator = favoriteStar.get();

        mEditStateTexture[0] = getContext().textures->get(Textures::EditIcon);
        mEditStateTexture[1] = getContext().textures->get(Textures::EditIconBlured);

        SceneNode::Ptr editIcon(new RectangleNode(
            &getContext(),
            sf::Vector2f(40.f, 40.f),
            getContext().textures->get(Textures::EditIcon)
        ));
        editIcon->setPosition(59.f + mWordIndicator->getLocalBounds().width + 50.f, 44.f);
        editIcon->setOnHover([this] (SceneNode& node) {
            ((RectangleNode*)&node)->setTexture(&mEditStateTexture[1]);
        });
        editIcon->setOnLostHover([this] (SceneNode& node) {
            ((RectangleNode*)&node)->setTexture(&mEditStateTexture[0]);
        });
        editIcon->setOnClick([this] (SceneNode& node) {
            Intent::Ptr intent(new Intent());
            intent->putExtra("word", mWordIndicator->getString().toAnsiString());
            intent->putExtra("definition", mDefinitions[mPagerIndex]);
            intent->putExtra("definitionId", mPagerIndex);
            requestStackPush(Activities::EDITDEFINITION, std::move(intent), EDIT);
        });
        mEditIndicator = editIcon.get();

        mDeleteStateTexture[0] = getContext().textures->get(Textures::DeleteIcon);
        mDeleteStateTexture[1] = getContext().textures->get(Textures::DeleteIconBlured);

        SceneNode::Ptr deleteIcon(new RectangleNode(
            &getContext(),
            sf::Vector2f(40.f, 40.f),
            getContext().textures->get(Textures::DeleteIcon)
        ));
        deleteIcon->setPosition(59.f + mWordIndicator->getLocalBounds().width + 100.f, 44.f);
        deleteIcon->setOnHover([this] (SceneNode& node) {
            ((RectangleNode*)&node)->setTexture(&mDeleteStateTexture[1]);
        });
        deleteIcon->setOnLostHover([this] (SceneNode& node) {
            ((RectangleNode*)&node)->setTexture(&mDeleteStateTexture[0]);
        });
        deleteIcon->setOnClick([this] (SceneNode& node) {
            requestStackPush(Activities::WORDDELCONFIRM, Intent::Ptr(new Intent()), DELETE);
        });
        mDeleteIndicator = deleteIcon.get();

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

        SceneNode::Ptr noDefinitionsFound(new TextNode(
            &getContext(), 
            "No definitions found", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xEF2424FF)
        ));
        noDefinitionsFound->setOrigin(
            noDefinitionsFound->getLocalBounds().left + noDefinitionsFound->getLocalBounds().width / 2.f,
            noDefinitionsFound->getLocalBounds().top + noDefinitionsFound->getLocalBounds().height / 2.f
        );
        noDefinitionsFound->setPosition(500.f, 300.f);
        mNoDefinitionsFound = noDefinitionsFound.get();
        mNoDefinitionsFound->disable();

        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionBackground));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionCore));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(wordText));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(favoriteStar));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(editIcon));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(deleteIcon));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionFrame));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(definitionIdText));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(prevButton));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(nextButton));
        mSceneLayers[DefinitionBackground]->attachChild(std::move(noDefinitionsFound));

        fixPageIndicatorPosition();
    }


    // Definition Page
    {
        mSceneLayers[DefinitionPage]->setPosition(0, 250.f);
        loadDefinitions();
        std::cout<<"meow"<<std::endl;
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

    if(mDefinitions.empty())
    {
        mNoDefinitionsFound->enable();
        mFavoriteIndicator->disable();
        mEditIndicator->disable();
        mDeleteIndicator->disable();
        mNextButton->disable();
        mPrevButton->disable();
        mDefinitionIdIndicator->disable();
        return;
    }

    mNoDefinitionsFound->disable();
    mFavoriteIndicator->enable();
    mEditIndicator->enable();
    mDeleteIndicator->enable();
    mNextButton->enable();
    mPrevButton->enable();
    mDefinitionIdIndicator->enable();

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

void ActivityDictionary::displayWord(const std::string& word)
{
    API* api = getContext().api;
    mDefinitions = api->get_definition_from_word(word);
    mIsFavorite = api->is_favorite(word);

    mWordIndicator->setString(word);
    mFavoriteIndicator->setPosition(59.f + mWordIndicator->getLocalBounds().width, 44.f);
    mEditIndicator->setPosition(59.f + mWordIndicator->getLocalBounds().width + 50.f, 44.f);
    mDeleteIndicator->setPosition(59.f + mWordIndicator->getLocalBounds().width + 100.f, 44.f);
    ((RectangleNode*)mFavoriteIndicator)->setTexture(&mFavoriteStateTexture[mIsFavorite]);
    loadDefinitions();
}

void ActivityDictionary::onBackActivity(int resultCode, Activity::Intent::Ptr intent)
{
    if(resultCode == FAVORITE)
    {
        if(intent == nullptr) return;
        std::string word = intent->getExtra<std::string>("word");
        displayWord(word);
    }
    else if(resultCode == FAVORITE_CONFIRM)
    {
        if(intent == nullptr) return;
        bool confirmed = intent->getExtra<bool>("confirmed");
        if(!confirmed) return;
        mIsFavorite = !mIsFavorite;
        ((RectangleNode*)mFavoriteIndicator)->setTexture(&mFavoriteStateTexture[mIsFavorite]);
        getContext().api->set_favorite(mWordIndicator->getString(), mIsFavorite);
    }
    else if(resultCode == DELETE)
    {
        if(intent == nullptr) return;
        bool confirmed = intent->getExtra<bool>("confirmed");
        if(!confirmed) return;
        getContext().api->delete_word(mWordIndicator->getString());
        displayWord("");
    }
    else if(resultCode == EDIT)
    {
        if(intent == nullptr) return;
        std::string word = intent->getExtra<std::string>("word");
        displayWord(word);
    }
    else if(resultCode == ADD)
    {
        if(intent == nullptr) return;
        std::string word = intent->getExtra<std::string>("word");
        displayWord(word);
    }
}