#include <iostream>
#include <Activity/ActivityGameOver.hpp>

ActivityGameOver::ActivityGameOver(ActivityStack& stack, Context context, Intent::Ptr intent)
: Activity(stack, context, std::move(intent))
, mSceneGraph(new SceneNode(&getContext()))
// , mPager(new Pager(&getContext(), intent->getExtra<std::vector<std::string>>("wrongAnswers")))
{
    mScore = getIntent()->getExtra<int>("score");
    mTime = getIntent()->getExtra<sf::Time>("totalTime");

    buildScene();
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

    // Back button
    SceneNode::Ptr backTextButton(new TextNode(
        &getContext(), 
        "Back", 
        getContext().fonts->get(Fonts::DEFAULT), 
        50,
        sf::Color(0xFFFFFFFF)
    ));
    backTextButton->setOnClick([this] (SceneNode& node) {
        requestStackPop();
        requestStackPush(Activities::GAMEOPTIONS);
    });
    backTextButton->setOnLostHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
    });
    backTextButton->setOnHover([this] (SceneNode& node) {
        ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
    });
    backTextButton->setPosition(26.f, 24.f - 7.f);
    mSceneGraph->attachChild(std::move(backTextButton));

    // Title
    SceneNode::Ptr title(new TextNode(
        &getContext(), 
        "Result", 
        getContext().fonts->get(Fonts::DEFAULT), 
        105,
        sf::Color(0xFFFFFFFF)
    ));
    title->setOrigin(
        title->getLocalBounds().width / 2.f + title->getLocalBounds().left,
        title->getLocalBounds().top
    );
    title->setPosition(getContext().window->getSize().x / 2.f, 41.f);

    mSceneLayers[Title]->attachChild(std::move(title));

    // Grading
    SceneNode::Ptr correctText(new TextNode(
        &getContext(), 
        "Correct: " + std::to_string(mScore) + "/10",
        getContext().fonts->get(Fonts::DEFAULT), 
        80,
        sf::Color(0xFFFFFFFF)
    ));
    correctText->setOrigin(
        correctText->getLocalBounds().left,
        correctText->getLocalBounds().top
    );
    correctText->setPosition(133.f, 198.f);

    SceneNode::Ptr gradeText(new TextNode(
        &getContext(), 
        "Rank: " + getRank(mScore),
        getContext().fonts->get(Fonts::DEFAULT), 
        80,
        sf::Color(0xFFFFFFFF)
    ));
    gradeText->setOrigin(
        gradeText->getLocalBounds().left,
        0.f
    );
    gradeText->setPosition(0.f, 24.f + correctText->getLocalBounds().height);

    correctText->attachChild(std::move(gradeText));
    mSceneLayers[Grading]->attachChild(std::move(correctText));

    // Timing
    SceneNode::Ptr averageTimeText(new TextNode(
        &getContext(), 
        "Average: " + std::to_string((int)(mTime.asSeconds() / 10.f)) + "s",
        getContext().fonts->get(Fonts::DEFAULT), 
        80,
        sf::Color(0xFFFFFFFF)
    ));
    averageTimeText->setOrigin(
        averageTimeText->getLocalBounds().left,
        averageTimeText->getLocalBounds().top
    );
    averageTimeText->setPosition(623.f, 198.f);

    SceneNode::Ptr totalTimeText(new TextNode(
        &getContext(), 
        "Total: " + std::to_string((int)mTime.asSeconds()) + "s",
        getContext().fonts->get(Fonts::DEFAULT), 
        80,
        sf::Color(0xFFFFFFFF)
    ));
    totalTimeText->setOrigin(
        totalTimeText->getLocalBounds().left,
        0.f
    );
    totalTimeText->setPosition(0.f, 24.f + averageTimeText->getLocalBounds().height);

    averageTimeText->attachChild(std::move(totalTimeText));
    mSceneLayers[Timing]->attachChild(std::move(averageTimeText));

    // Wrong answers
    mSceneLayers[WrongAnswers]->setPosition(26.f, 481.f);
    SceneNode::Ptr wrongAnswersText(new RectangleNode(
        &getContext(), 
        sf::Vector2f(944.f, 287.f),
        getContext().textures->get(Textures::WrongAnswersBackground)
    ));

    SceneNode::Ptr wrongAnswersTitle(new TextNode(
        &getContext(), 
        "Wrong Answers",
        getContext().fonts->get(Fonts::DEFAULT), 
        50,
        sf::Color(0xFFFFFFFF)
    ));
    wrongAnswersTitle->setOrigin(
        wrongAnswersTitle->getLocalBounds().left,
        wrongAnswersTitle->getLocalBounds().top + wrongAnswersTitle->getLocalBounds().height
    );
    wrongAnswersTitle->setPosition(50.f-26.f, -2.f);
    
    mSceneLayers[WrongAnswers]->attachChild(std::move(wrongAnswersText));
    mSceneLayers[WrongAnswers]->attachChild(std::move(wrongAnswersTitle));
}

void ActivityGameOver::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());
    window.draw(*mSceneGraph);
    // window.draw(*mPager);
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

std::string ActivityGameOver::getRank(int score)
{
    if (score >= 9)
        return "S";
    else if (score >= 8)
        return "A";
    else if (score >= 7)
        return "B";
    else if (score >= 6)
        return "C";
    else if (score >= 5)
        return "D";
    else
        return "F";
}

ActivityGameOver::Pager::Pager(Context* context, const std::vector<std::string>& pageTexts)
: SceneNode(context)
, mPageTexts(pageTexts)
, mIndex(0)
{
    for(int i=0; i<pageTexts.size(); i++) 
    {
        mPages.push_back(SceneNode::Ptr(new TextNode(
            context,
            pageTexts[i],
            context->fonts->get(Fonts::DEFAULT),
            50,
            sf::Color(0xFFFFFFFF)
        )));
        fixPosition(i);
    }

    prevButton = SceneNode::Ptr(new TextNode(
        context,
        "<",
        context->fonts->get(Fonts::DEFAULT),
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

    nextButton = SceneNode::Ptr(new TextNode(
        context,
        ">",
        context->fonts->get(Fonts::DEFAULT),
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

    mPageIndicator = TextNode::Ptr(new TextNode(
        context,
        std::to_string(mIndex+1) + "/" + std::to_string((pageTexts.size() / 9) + 1),
        context->fonts->get(Fonts::DEFAULT),
        50,
        sf::Color(0xFFFFFFFF)
    ));
    ((TextNode*)mPageIndicator.get())->alignCenter();

    fixPageIndicatorPosition();
}

void ActivityGameOver::Pager::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(int i=9*mIndex; i<9*(mIndex+1); i++) 
    {
        if (i >= mPageTexts.size())
            break;
        target.draw(*mPages[i], states);
    }
    target.draw(*prevButton, states);
    target.draw(*nextButton, states);
    target.draw(*mPageIndicator, states);
}

bool ActivityGameOver::Pager::handleEventCurrent(const sf::Event& event)
{
    for(int i=9*mIndex; i<9*(mIndex+1); i++) 
    {
        if (i >= mPageTexts.size())
            break;
        mPages[i]->handleEvent(event);
    }
    prevButton->handleEvent(event);
    nextButton->handleEvent(event);
    return false;
}

bool ActivityGameOver::Pager::handleRealtimeInputCurrent()
{
    for(int i=9*mIndex; i<9*(mIndex+1); i++) 
    {
        if (i >= mPageTexts.size())
            break;
        mPages[i]->handleRealtimeInput();
    }
    prevButton->handleRealtimeInput();
    nextButton->handleRealtimeInput();
    return false;
}

void ActivityGameOver::Pager::nextPage()
{
    if (mIndex < (mPageTexts.size() / 9))
    {
        mIndex++;
        setPagerIndex(mIndex);
    }
}

void ActivityGameOver::Pager::prevPage()
{
    if (mIndex > 0)
    {
        mIndex--;
        setPagerIndex(mIndex);
    }
}

void ActivityGameOver::Pager::setPagerIndex(int index)
{
    mIndex = index;
    if(index == 0) {
        prevButton->setOnClick([] (SceneNode& node) {});
        prevButton->setOnLostHover([] (SceneNode& node) {    
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
    }
    else {
        prevButton->setOnClick([this] (SceneNode& node) {
            prevPage();
        });
        prevButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
    }

    if(index == (mPageTexts.size() / 9)) {
        nextButton->setOnClick([] (SceneNode& node) {});
        nextButton->setOnLostHover([] (SceneNode& node) {    
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFF7F));
        });
    }
    else {
        nextButton->setOnClick([this] (SceneNode& node) {
            nextPage();
        });
        nextButton->setOnLostHover([this] (SceneNode& node) {
            ((TextNode*)&node)->setColor(sf::Color(0xFFFFFFFF));
        });
    }

    ((TextNode*)mPageIndicator.get())->setString(std::to_string(mIndex+1) + "/" + std::to_string((mPageTexts.size() / 9) + 1));
    fixPageIndicatorPosition();
}

void ActivityGameOver::Pager::fixPosition(int index)
{
    int x = index % 3;
    int y = index / 3;
    SceneNode* node = (TextNode*)mPages[index].get();
    if(x == 0) {
        node->setOrigin(
            node->getLocalBounds().left,
            node->getLocalBounds().top
        );
        node->setPosition(
            61.f,
            26.f + (117.f - 26.f) * y
        );
    }
    else if(x == 1) {
        node->setOrigin(
            node->getLocalBounds().left + node->getLocalBounds().width / 2.f,
            node->getLocalBounds().top
        );
        node->setPosition(
            500.f,
            26.f + (117.f - 26.f) * y
        );
    }
    else if(x == 2) {
        node->setOrigin(
            node->getLocalBounds().left + node->getLocalBounds().width,
            node->getLocalBounds().top
        );
        node->setPosition(
            1000.f - 61.f,
            26.f + (117.f - 26.f) * y
        );
    }
}

void ActivityGameOver::Pager::fixPageIndicatorPosition()
{
    const float beyond = 50.f;
    ((TextNode*)mPageIndicator.get())->alignCenter();
    mPageIndicator->setPosition(500.f, 800.f - (beyond));

    prevButton->setPosition(
        mPageIndicator->getPosition().x - ((TextNode*)mPageIndicator.get())->getLocalBounds().width / 2.f  - 10.f,
        800.f - (beyond)
    );

    nextButton->setPosition(
        mPageIndicator->getPosition().x + ((TextNode*)mPageIndicator.get())->getLocalBounds().width / 2.f  + 10.f,
        800.f - (beyond)
    );
}