#pragma once
#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>
#include <ActivityStack.hpp>
#include <API.hpp>
#include <API_Dummy_0.hpp>

class Application
{
public:
    Application();
    void run();

private:
    void registerStates();
    void processInput();
    void update(sf::Time dt);
    void updateStatistics(sf::Time elapsedTime);
    void draw();

private:
    std::unique_ptr<API>            mAPI;
    sf::RenderWindow                mWindow;
    std::unique_ptr<TextureHolder>  mTextures;
    std::unique_ptr<FontHolder>     mFonts;
    bool                            mIsPaused;
    bool                            mIsShowingStatistics;
    sf::Text                        mStatisticsText;
    sf::Time                        mStatisticsUpdateTime;
	int                             mStatisticsNumFrames;
    ActivityStack                   mActivityStack;
    Json::Value                     mData;

private:
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
};