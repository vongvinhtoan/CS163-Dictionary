#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityHistory : public Activity
{
private:
    const int maxDisplay = 18;
    std::unique_ptr<SceneNode> mSceneGraph;

private:
    void   buildScene();
    void   buttonize(SceneNode* node);
    void   buildHistories(const std::vector<std::string>& histories);
    void   fixPosition(int index);
    void   nextPage();
    void   prevPage();
    void   setPagerIndex(int index);
    void   fixPageIndicator();

public:
    ActivityHistory(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    SceneNode*                  mFavoriteHolder;
    TextNode*                   mPageIndicator;
    TextNode*                   mNextButton;
    TextNode*                   mPrevButton;
    SceneNode*                  mNoFavoritesFound;
    std::vector<SceneNode*>     mFavorites;
    int                         mPagerIndex;
};