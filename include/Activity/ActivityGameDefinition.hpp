#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <Randomizer.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityGameDefinition : public Activity
{
private:
    enum Layer
    {
        Background,
        Taskbar,
        Definition,
        Playzone,
        Footer,
        LayerCount
    };

    std::unique_ptr<SceneNode> mSceneGraph;
    std::unique_ptr<SceneNode> mResultAnnouncer;
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void   buildScene();

public:
    ActivityGameDefinition(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    void            nextQuestion();
    void            checkAnswer(int index);
    void            loadQuestion();
    void            endGame();
    void            disfunctionButtons();
    void            refunctionButtons();
    void            correctLayout();

protected:
    SceneNode*      mDefinitionCore;
    TextNode*       mDefinitionText;
    TextNode*       mDefinition;
    TextNode*       mQuestionIndicator;
    TextNode*       mTimeIndicator;
    TextNode*       mScoreIndicator;
    TextNode*       mResultIndicator;
    ButtonNode*     mOptions[4];
    RectangleNode*  mResultOverlay;

    enum WatchResult
    {
        NotWatching,
        CorrectResult,
        WrongResult,
        TimeOutResult
    };

    const sf::Time              mTimePerQuestion = sf::seconds(10);
    const sf::Time              mTimeWaitResult = sf::seconds(1.25f);
    sf::Time                    mTimeLeft;
    sf::Time                    mTimeResult;
    int                         mQuestionIndex;
    int                         mScore;
    int                         mCorrectAnswerIndex;
    int                         mAnswerIndex;
    int                         mIsWatchingResult;
    std::string                 mOptionTexts[4];
    std::vector<std::string>    mWrongAnswers;
    sf::Time                    mTotalTime;
};