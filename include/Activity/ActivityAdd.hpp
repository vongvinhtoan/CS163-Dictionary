#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>
#include <SceneNode\SearchbarNode.hpp>

class ActivityAdd : public Activity
{
private:
    std::unique_ptr<SceneNode> mSceneGraph;

private:
    void   buildScene();

public:
    ActivityAdd(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    SearchbarNode*              mAddWordBar;
    SearchbarNode*               mAddDefBar;
};