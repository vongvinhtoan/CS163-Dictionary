#include <Application.hpp>
#include <iostream>
#include <string>
#include <Activity/ActivityDashboard.hpp>
#include <Activity/ActivityCredit.hpp>
#include <Activity/ActivityGameOption.hpp>
#include <Activity/ActivityGameDefinition.hpp>
#include <Activity/ActivityGameOver.hpp>

Application::Application() 
: mWindow(sf::VideoMode(1000, 800), "Dictionary", sf::Style::Close)
// , mStateStack(State::Context(mWindow, mTextures, mFonts, mData, *mDialogOpener, *mRandomizer))
, mIsPaused(false)
, mStatisticsNumFrames(0)
, mStatisticsUpdateTime()
, mIsShowingStatistics(false)
, mTextures(new TextureHolder())
, mFonts(new FontHolder())
, mActivityStack(Activity::Context(mWindow, *mTextures, *mFonts, mData))
, mAPI(new API_Dummy_0())
{
    // readJSON();
    mFonts->load(Fonts::DEFAULT, "data/fonts/Karantina.ttf");
    mTextures->load(Textures::MenuBackground, "data/textures/MenuBackground.png");
    mTextures->load(Textures::StartingFrameBackground, "data/textures/StartingFrameBackground.png");
    mTextures->load(Textures::Footer, "data/textures/Footer.png");
    mTextures->load(Textures::Logo, "data/textures/Logo.png");
    mTextures->load(Textures::WoodenBackground1, "data/textures/WoodenBackground1.png");
    mTextures->load(Textures::WoodenBackground2, "data/textures/WoodenBackground2.png");
    mTextures->load(Textures::GameBackground, "data/textures/GameBackground.png");
    mTextures->load(Textures::PlayzoneBackground, "data/textures/PlayzoneBackground.png");
    mTextures->load(Textures::DefinitionBackground, "data/textures/DefinitionBackground.png");
    mTextures->load(Textures::DefinitionCore, "data/textures/DefinitionCore.png");
    mTextures->load(Textures::GameOverBackground, "data/textures/GameOverBackground.png");
    mTextures->load(Textures::WrongAnswersBackground, "data/textures/WrongAnswersBackground.png");
    
    registerActivities();
    mActivityStack.pushActivity(Activities::DASHBOARD);
    mActivityStack.draw();

	mStatisticsText.setFont(mFonts->get(Fonts::DEFAULT));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(40);
    mStatisticsText.setFillColor(sf::Color(0, 0, 0, 255));
    mWindow.setFramerateLimit(60);
}

void Application::registerActivities() 
{
    mActivityStack.registerActivity<ActivityDashboard>(Activities::DASHBOARD);
    mActivityStack.registerActivity<ActivityCredit>(Activities::CREDIT);
    mActivityStack.registerActivity<ActivityGameOption>(Activities::GAMEOPTIONS);
    mActivityStack.registerActivity<ActivityGameDefinition>(Activities::GAMEDEFINITION);
    mActivityStack.registerActivity<ActivityGameOver>(Activities::GAMEOVER);
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time elapsed             = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        if(mActivityStack.isEmpty()) mWindow.close();

        processInput();
        elapsed = clock.restart();
        timeSinceLastUpdate += elapsed;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            if(!mIsPaused) update(TimePerFrame);
        }
        updateStatistics(elapsed);
        draw();
    }
}

void Application::processInput()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(!mIsPaused) mActivityStack.handleEvent(event);
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::GainedFocus:
                mIsPaused = false;
                break;
            case sf::Event::LostFocus:
                mIsPaused = true;
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::F5) mIsShowingStatistics ^= true;
                break;
        }
    }
    if(!mIsPaused) mActivityStack.handleRealtimeInput();
}

void Application::update(sf::Time dt)
{
    mActivityStack.update(dt);
}

void Application::draw()
{
    mWindow.clear();
    mActivityStack.draw();
    
    mWindow.setView(mWindow.getDefaultView());
    if(mIsShowingStatistics) {
        mWindow.draw(mStatisticsText);
    }
    mWindow.display();
}

void Application::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"FPS = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us"
        );					 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}