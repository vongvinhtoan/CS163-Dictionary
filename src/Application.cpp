#include <Application.hpp>
#include <iostream>
#include <string>
#include <ActivityDashboard.hpp>

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
    mFonts->load(Fonts::DEFAULT, "data/fonts/Sansation.ttf");
    mTextures->load(Textures::MenuBackground, "data/textures/MenuBackground.png");
    mTextures->load(Textures::StartingFrameBackground, "data/textures/StartingFrameBackground.png");
    mTextures->load(Textures::Footer, "data/textures/Footer.png");
    mTextures->load(Textures::Logo, "data/textures/Logo.png");
    
    registerActivities();
    mActivityStack.pushActivity(Activities::DASHBOARD);
    mActivityStack.draw();

	mStatisticsText.setFont(mFonts->get(Fonts::DEFAULT));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
    mStatisticsText.setFillColor(sf::Color(0, 0, 0, 255));
    mWindow.setFramerateLimit(60);
}

void Application::registerActivities() 
{
    mActivityStack.registerActivity<ActivityDashboard>(Activities::DASHBOARD);
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