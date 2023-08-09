#include <Application.hpp>
#include <iostream>
#include <string>

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
    
    registerStates();
    // mActivityStack.pushActivity(Activities::MENU);
    mActivityStack.draw();

	mStatisticsText.setFont(mFonts->get(Fonts::DEFAULT));
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);
    mWindow.setFramerateLimit(60);
}

void Application::registerStates() 
{

}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time elapsed             = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        // if(mStateStack.isEmpty()) mWindow.close();

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
        // mStateStack.handleEvent(event);
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
    // mStateStack.handleRealtimeInput();
}

void Application::update(sf::Time dt)
{
    // mStateStack.update(dt);
}

void Application::draw()
{
    mWindow.clear();
    // mStateStack.draw();
    
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