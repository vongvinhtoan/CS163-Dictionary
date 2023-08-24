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
    sf::Time                    mTime;

private:
    class Pager : public SceneNode
    {
    private:
        std::vector<SceneNode::Ptr> mPages;
        std::vector<std::string>    mPageTexts;
        int                         mIndex;
        SceneNode::Ptr              prevButton;
        SceneNode::Ptr              nextButton;
        SceneNode::Ptr              mPageIndicator;
        
    public:
        Pager(Context* context, const std::vector<std::string>& pageTexts);

    private:
        virtual void    drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void    handleEventCurrent(const sf::Event& event, int& command);
        virtual void    handleRealtimeInputCurrent(int& command);
        void            nextPage();
        void            prevPage();
        void            setPagerIndex(int index);
        void            fixPosition(int index);
        void            fixPageIndicatorPosition();
    };
    std::unique_ptr<Pager>      mPager;
};