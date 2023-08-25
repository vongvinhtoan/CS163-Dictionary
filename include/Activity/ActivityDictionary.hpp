#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityDictionary : public Activity
{
private:
    enum Layer
    {
        Background,
        Taskbar,
        DefinitionBackground,
        DefinitionPage,
        Footer,
        LayerCount
    };

    std::unique_ptr<SceneNode> mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void   buildScene();
    void   buttonize(SceneNode* node);

public:
    ActivityDictionary(ActivityStack& stack, Context context, Intent::Ptr intent);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    SceneNode*                  mDictionaryOptionsButton[Database::DictionaryId::SIZE];
    SceneNode*                  mWordIndicator;
    SceneNode*                  mFavoriteIndicator;
    SceneNode*                  mNextButton;
    SceneNode*                  mPrevButton;
    SceneNode*                  mDefinitionIdIndicator;
    bool                        mIsFavorite;
    int                         mPagerIndex;
    sf::Texture                 mFavoriteStateTexture[2];
    std::size_t                 mDictionaryId;
    std::vector<std::string>    mDefinitions;
    std::vector<SceneNode*>     mPages;

private:
    void fixPageIndicatorPosition();
    void nextPage();
    void prevPage();
    void setPagerIndex(int index);
    void loadDefinitions();
};