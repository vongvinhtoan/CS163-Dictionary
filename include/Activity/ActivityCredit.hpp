#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityCredit : public Activity
{
private:
    enum Layer
    {
        Background,
        Title,
        Names,
        LayerCount
    };

    std::unique_ptr<SceneNode> mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void   buildScene();

public:
    ActivityCredit(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();
};