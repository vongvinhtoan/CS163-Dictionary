#include <iostream>
#include <Activity/ActivityGameDefinition.hpp>

ActivityGameDefinition::ActivityGameDefinition(ActivityStack& stack, Context context)
: Activity(stack, context)
, mSceneGraph(new SceneNode(&getContext()))
, mResultAnnouncer(new SceneNode(&getContext()))
, mQuestionIndex(1)
, mScore(0)
, mIsWatchingResult(NotWatching)
{
    buildScene();
    loadQuestion();
}

void ActivityGameDefinition::buildScene()
{
    // Initialize layers
    for (std::size_t i = 0; i < LayerCount; ++i)
    {
        SceneNode::Ptr layer(new SceneNode(&getContext()));
        mSceneLayers[i] = layer.get();
        mSceneGraph->attachChild(std::move(layer));
    }

    // Background layer (done)
    {
        SceneNode::Ptr background(new RectangleNode(
            &getContext(), 
            sf::Vector2f(1000.f, 400.f),
            getContext().textures->get(Textures::GameBackground)
        ));
        mSceneLayers[Background]->attachChild(std::move(background));
    }

    // Taskbar layer
    {
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
        backTextButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        backTextButton->setOnHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
        backTextButton->setPosition(16.7f, -7.f);

        SceneNode::Ptr tutorialTextButton(new TextNode(
            &getContext(), 
            "Tutorial", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        tutorialTextButton->setOnClick([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
            requestStackPush(Activities::GAMEDEFINITIONTOUR);
        });
        tutorialTextButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        tutorialTextButton->setOnHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
        tutorialTextButton->setOrigin(
            tutorialTextButton->getLocalBounds().width + tutorialTextButton->getLocalBounds().left,
            0.f
        );
        tutorialTextButton->setPosition(
            taskbar->getLocalBounds().width - 16.7f,
            -7.f
        );

        SceneNode::Ptr skipTextButton(new TextNode(
            &getContext(), 
            "Skip", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        skipTextButton->setOnClick([this] (SceneNode& node) {
            if(mQuestionIndex == 10) {
                endGame();
            } else {
                nextQuestion();
            }
        });
        skipTextButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
        skipTextButton->setOnHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
        skipTextButton->setOrigin(
            skipTextButton->getLocalBounds().width + skipTextButton->getLocalBounds().left,
            0.f
        );
        skipTextButton->setPosition(
            taskbar->getLocalBounds().width - 16.7f * 2
            - tutorialTextButton->getLocalBounds().width - tutorialTextButton->getLocalBounds().left - 16.7f,
            -7.f
        );

        SceneNode::Ptr questionIndicator(new TextNode(
            &getContext(), 
            "Question: 1/10", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        questionIndicator->setOrigin(
            questionIndicator->getLocalBounds().width / 2 + questionIndicator->getLocalBounds().left,
            0.f
        );
        questionIndicator->setPosition(
            taskbar->getLocalBounds().width / 2.f,
            -7.f
        );

        mQuestionIndicator = (TextNode*)questionIndicator.get();

        taskbar->attachChild(std::move(backTextButton));
        taskbar->attachChild(std::move(tutorialTextButton));
        taskbar->attachChild(std::move(skipTextButton));
        taskbar->attachChild(std::move(questionIndicator));

        mSceneLayers[Taskbar]->attachChild(std::move(taskbar));
    }

    // Definition layer
    {
        mSceneLayers[Definition]->setPosition(0.f, 114.f);

        SceneNode::Ptr definitionBackground(new RectangleNode(
            &getContext(), 
            sf::Vector2f(1000.f, 215.f),
            getContext().textures->get(Textures::DefinitionBackground)
        ));

        SceneNode::Ptr definitionCore(new RectangleNode(
            &getContext(),
            sf::Vector2f(1000.f, 150.f),
            getContext().textures->get(Textures::DefinitionCore)
        ));
        definitionCore->setPosition(
            0.f,
            (definitionBackground->getLocalBounds().height - definitionCore->getLocalBounds().height) / 2.f 
        );

        SceneNode::Ptr definitionText(
            new TextNode(&getContext(), 
            "Definition", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFF0000FF)));
        definitionText->setOrigin(
            definitionText->getLocalBounds().width / 2.f + definitionText->getLocalBounds().left,
            0.f
        );
        definitionText->setPosition(
            definitionCore->getLocalBounds().width / 2.f,
            0.f
        );

        SceneNode::Ptr definition(
            new TextNode(&getContext(), 
            "Not just a Definition", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0x000000FF)));
        definition->setOrigin(
            definition->getLocalBounds().width / 2.f + definition->getLocalBounds().left,
            0.f
        );
        definition->setPosition(
            definitionCore->getLocalBounds().width / 2.f,
            definitionText->getLocalBounds().height + definitionText->getLocalBounds().top
        );

        mDefinitionCore = definitionCore.get();
        mDefinitionText = (TextNode*)definitionText.get();
        mDefinition = (TextNode*)definition.get();

        definitionCore->attachChild(std::move(definitionText));
        definitionCore->attachChild(std::move(definition));
        definitionBackground->attachChild(std::move(definitionCore));

        mSceneLayers[Definition]->attachChild(std::move(definitionBackground));
    }

    // Playzone layer
    {
        mSceneLayers[Playzone]->setPosition(0.f, 400.f);

        SceneNode::Ptr playzoneBackground1(new RectangleNode(
            &getContext(), 
            sf::Vector2f(1000.f, 400.f),
            sf::Color(0x606060FF)
        ));

        SceneNode::Ptr playzoneBackground2(new RectangleNode(
            &getContext(), 
            sf::Vector2f(974.026f, 381.818f),
            getContext().textures->get(Textures::PlayzoneBackground)
        ));
        playzoneBackground2->setPosition(13.f, 8.f);

        SceneNode::Ptr timeIndicator(new TextNode(
            &getContext(), 
            "Time: 10s", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        timeIndicator->setOrigin(
            timeIndicator->getLocalBounds().left,
            timeIndicator->getLocalBounds().top
        );
        timeIndicator->setPosition(39.f, 27.f);
        mTimeIndicator = (TextNode*)timeIndicator.get();

        SceneNode::Ptr scoreIndicator(new TextNode(
            &getContext(), 
            "Correct: 10/10", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0xFFFFFFFF)
        ));
        scoreIndicator->setOrigin(
            scoreIndicator->getLocalBounds().width + scoreIndicator->getLocalBounds().left,
            scoreIndicator->getLocalBounds().top
        );
        scoreIndicator->setPosition(
            playzoneBackground1->getLocalBounds().width - 39.f,
            27.f
        );
        mScoreIndicator = (TextNode*)scoreIndicator.get();

        SceneNode::Ptr options[4];

        for(int i=0; i<4; i++) {
            options[i] = SceneNode::Ptr(new ButtonNode(
                &getContext(), 
                sf::Vector2f(350.f, 88.9f),
                "Option " + std::to_string(i + 1),
                50
            ));
            options[i]->setOnClick([this, i] (SceneNode& node) {
                checkAnswer(i);
            });
            mOptions[i] = (ButtonNode*)options[i].get();
        }
        mOptions[0]->setPosition(65.93f, 84.f);
        mOptions[1]->setPosition(65.93f, 231.f);
        mOptions[2]->setPosition(583.42f, 84.f);
        mOptions[3]->setPosition(583.42f, 231.f);

        mSceneLayers[Playzone]->attachChild(std::move(playzoneBackground1));
        mSceneLayers[Playzone]->attachChild(std::move(playzoneBackground2));
        mSceneLayers[Playzone]->attachChild(std::move(timeIndicator));
        mSceneLayers[Playzone]->attachChild(std::move(scoreIndicator));
        for(int i=0; i<4; i++) {
            mSceneLayers[Playzone]->attachChild(std::move(options[i]));
        }
    }

    // Footer layer
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

    // Result Announcer
    {
        SceneNode::Ptr resultAnnouncerBackground1(new RectangleNode(
            &getContext(), 
            sf::Vector2f(350.f, 150.f), 
            sf::Color(0x606060FF)
        ));
        mResultAnnouncer->setPosition(
            (getContext().window->getSize().x - resultAnnouncerBackground1->getLocalBounds().width) / 2.f,
            325.f
        );

        SceneNode::Ptr resultAnnouncerBackground2(new RectangleNode(
            &getContext(), 
            sf::Vector2f(320.f, 120.f), 
            sf::Color(0xFFFFFFFF)
        ));
        resultAnnouncerBackground2->setPosition(
            (resultAnnouncerBackground1->getLocalBounds().width - resultAnnouncerBackground2->getLocalBounds().width) / 2.f,
            (resultAnnouncerBackground1->getLocalBounds().height - resultAnnouncerBackground2->getLocalBounds().height) / 2.f
        );

        SceneNode::Ptr resultAnnouncerText(new TextNode(
            &getContext(), 
            "Correct!", 
            getContext().fonts->get(Fonts::DEFAULT), 
            50,
            sf::Color(0x000000FF)
        ));

        mResultIndicator = (TextNode*)resultAnnouncerText.get();

        resultAnnouncerText->setOrigin(
            resultAnnouncerText->getLocalBounds().width / 2.f + resultAnnouncerText->getLocalBounds().left,
            resultAnnouncerText->getLocalBounds().height / 2.f + resultAnnouncerText->getLocalBounds().top
        );
        resultAnnouncerText->setPosition(
            resultAnnouncerBackground2->getLocalBounds().width / 2.f,
            resultAnnouncerBackground2->getLocalBounds().height / 2.f
        );

        SceneNode::Ptr resultAnnouncerOverlay(new RectangleNode(
            &getContext(), 
            sf::Vector2f(350.f, 150.f), 
            sf::Color(0x0000007F)
        ));
        mResultOverlay = (RectangleNode*)resultAnnouncerOverlay.get();

        resultAnnouncerBackground2->attachChild(std::move(resultAnnouncerText));
        resultAnnouncerBackground1->attachChild(std::move(resultAnnouncerBackground2));
        mResultAnnouncer->attachChild(std::move(resultAnnouncerBackground1));
        mResultAnnouncer->attachChild(std::move(resultAnnouncerOverlay));
    }
}

void ActivityGameDefinition::loadQuestion()
{
    mTimeLeft = mTimePerQuestion;
    Randomizer& randomizer = Randomizer::getInstance();

    mDefinition->setString(std::string(randomizer.nextInt(2, 10), 'k'));

    mCorrectAnswerIndex = randomizer.nextInt(0, 3);

    for(int i=0; i<4; i++) {
        if(i == mCorrectAnswerIndex) {
            mOptions[i]->setText(mDefinition->getString());
        } else {
            mOptions[i]->setText(std::string(randomizer.nextInt(2, 10), 's'));
        }
    }
}

void ActivityGameDefinition::nextQuestion()
{
    mQuestionIndex++;
    loadQuestion();
    correctLayout();
}

void ActivityGameDefinition::checkAnswer(int index)
{
    mTimeResult = mTimeWaitResult;
    mAnswerIndex = index;
    if(index == mCorrectAnswerIndex) {
        mScore++;
        mIsWatchingResult = CorrectResult;
    }
    else if(index == -1) {
        mIsWatchingResult = TimeOutResult;
    }
    else {
        mIsWatchingResult = WrongResult;
    }
    disfunctionButtons();
}

void ActivityGameDefinition::endGame()
{
    requestStackPush(Activities::GAMEOVER);
}

void ActivityGameDefinition::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
    if(mIsWatchingResult != NotWatching) {
        window.draw(*mResultAnnouncer);
    }
}

bool ActivityGameDefinition::update(sf::Time dt)
{
    mSceneGraph->update(dt);

    correctLayout();

    if(mIsWatchingResult == NotWatching)
    {
        mTimeLeft -= dt;
        mTimeIndicator->setString("Time: " + std::to_string((int)mTimeLeft.asSeconds()) + "s");

        if(mTimeLeft <= sf::Time::Zero) {
            checkAnswer(-1);
        }
    }
    else
    {
        mTimeResult -= dt;
        mResultOverlay->setSize(sf::Vector2f(
            mResultOverlay->getLocalBounds().width,
            150.f * (1 - mTimeResult.asSeconds() / mTimeWaitResult.asSeconds())
        ));
        if(mTimeResult <= sf::Time::Zero) {
            mIsWatchingResult = NotWatching;
            refunctionButtons();
            if(mQuestionIndex == 10) {
                endGame();
            } else {
                nextQuestion();
            }
        }
    }
    
    return false;
}

void ActivityGameDefinition::correctLayout()
{
    ((RectangleNode*)mDefinitionCore)->setSize(sf::Vector2f(
        mDefinitionCore->getLocalBounds().width,
        mDefinitionText->getLocalBounds().height + mDefinition->getLocalBounds().height +
        mDefinitionText->getLocalBounds().top + mDefinition->getLocalBounds().top * 2
    ));
    mDefinitionCore->setPosition(
        (mDefinitionCore->getParent()->getLocalBounds().width - mDefinitionCore->getLocalBounds().width) / 2.f,
        (mDefinitionCore->getParent()->getLocalBounds().height - mDefinitionCore->getLocalBounds().height) / 2.f
    );

    ((SceneNode*)mDefinition)->setOrigin(
        mDefinition->getLocalBounds().width / 2.f + mDefinition->getLocalBounds().left,
        0.f
    );
    ((SceneNode*)mDefinition)->setPosition(
        mDefinitionCore->getLocalBounds().width / 2.f,
        mDefinitionText->getLocalBounds().height + mDefinitionText->getLocalBounds().top
    );

    mQuestionIndicator->setString("Question: " + std::to_string(mQuestionIndex) + "/10");
    ((SceneNode*)mQuestionIndicator)->setOrigin(
        mQuestionIndicator->getLocalBounds().width / 2 + mQuestionIndicator->getLocalBounds().left,
        0.f
    );
    ((SceneNode*)mQuestionIndicator)->setPosition(
        mQuestionIndicator->getParent()->getLocalBounds().width / 2.f,
        -7.f
    );

    mScoreIndicator->setString("Correct: " + std::to_string(mScore) + "/10");

    mResultIndicator->alignCenter();
    ((SceneNode*)mResultIndicator)->setPosition(
        mResultIndicator->getParent()->getLocalBounds().width / 2.f,
        mResultIndicator->getParent()->getLocalBounds().height / 2.f
    );
}

void ActivityGameDefinition::disfunctionButtons()
{
    for(int i=0; i<4; i++) {
        mOptions[i]->setOnClick([] (SceneNode& node) {});
        mOptions[i]->setOnLostHover([] (SceneNode& node) {});
        mOptions[i]->setOnHover([] (SceneNode& node) {});
        mOptions[i]->setOnHold([] (SceneNode& node) {});
        mOptions[i]->setBackgroundColor(sf::Color(0xA02C2C7F));
        mOptions[i]->setTextColor(sf::Color(0xFFFFFF7F));
    }
    
    if(mIsWatchingResult == CorrectResult) {
        mOptions[mAnswerIndex]->setBackgroundColor(sf::Color(0x3BC52FFF));
        mOptions[mAnswerIndex]->setTextColor(sf::Color(0xFFFFFFFF));
        mResultIndicator->setString("Congratulations!");
        mResultIndicator->setColor(sf::Color(0x36C22AFF));
    }
    else if(mIsWatchingResult == WrongResult) {
        mOptions[mAnswerIndex]->setBackgroundColor(sf::Color(0xA02C2CFF));
        mOptions[mAnswerIndex]->setTextColor(sf::Color(0xFFFFFFFF));
        mOptions[mCorrectAnswerIndex]->setBackgroundColor(sf::Color(0x3BC52FFF));
        mOptions[mCorrectAnswerIndex]->setTextColor(sf::Color(0xFFFFFFFF));
        mResultIndicator->setString("Opps! Wrong answer");
        mResultIndicator->setColor(sf::Color(0xC22A2AFF));

    }
    else if(mIsWatchingResult == TimeOutResult) {
        mOptions[mCorrectAnswerIndex]->setBackgroundColor(sf::Color(0x3BC52FFF));
        mOptions[mCorrectAnswerIndex]->setTextColor(sf::Color(0xFFFFFFFF));
        mResultIndicator->setString("Time out!");
        mResultIndicator->setColor(sf::Color(0xC22A2AFF));
    }

    correctLayout();
}

void ActivityGameDefinition::refunctionButtons()
{
    for(int i=0; i<4; i++) {
        mOptions[i]->setOnClick([this, i] (SceneNode& node) {
            checkAnswer(i);
        });
        mOptions[i]->setListeners();
        mOptions[i]->setTextColor(sf::Color(0xFFFFFFFF));
    }
}

bool ActivityGameDefinition::handleEvent(const sf::Event& event)
{
    mSceneGraph->handleEvent(event);
    return false;
}

bool ActivityGameDefinition::handleRealtimeInput()
{
    mSceneGraph->handleRealtimeInput();
    return false;
}