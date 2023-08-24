#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityGameOver : public Activity
{
private:
    enum Layer
    {
        Background,
        Title,
        Grading,
        Timing,
        WrongAnswers,
        LayerCount
    };

    std::unique_ptr<SceneNode> mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void        buildScene();
    std::string getRank(int score);

public:
    ActivityGameOver(ActivityStack& stack, Context context, Intent::Ptr intent);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    int                         mScore;
    std::vector<std::string>    mWrongAnswers;
    sf::Time                    mTime;
};