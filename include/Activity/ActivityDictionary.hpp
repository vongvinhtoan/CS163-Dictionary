#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>
#include <SceneNode\SearchbarNode.hpp>

class ActivityDictionary : public Activity
{
private:
    enum REQUEST_CODE
    {
        FAVORITE,
        ADD,
        COUNT
    };

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
    virtual void    onBackActivity(int resultCode, Activity::Intent::Ptr intent);

public:
    ActivityDictionary(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    SceneNode*                  mDictionaryOptionsButton[Database::DictionaryId::SIZE];
    TextNode*                   mWordIndicator;
    SceneNode*                  mFavoriteIndicator;
    SceneNode*                  mNextButton;
    SceneNode*                  mPrevButton;
    SceneNode*                  mDefinitionIdIndicator;
    SceneNode*                  mNoDefinitionsFound;
    SearchbarNode*              mSearchbar;
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
    void displayWord(const std::string& word);
};