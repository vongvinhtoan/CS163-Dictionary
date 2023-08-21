#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <Randomizer.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityGame : public Activity
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
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void   buildScene();

public:
    ActivityGame(ActivityStack& stack, Context context);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();

private:
    void            nextQuestion();
    void            checkAnswer(int index);
    void            loadQuestion();
    void            endGame();

protected:
    SceneNode*      mDefinitionCore;
    TextNode*       mDefinitionText;
    TextNode*       mDefinition;
    TextNode*       mQuestionIndicator;
    TextNode*       mTimeIndicator;
    TextNode*       mScoreIndicator;
    ButtonNode*     mOptions[4];


    const sf::Time  mTimePerQuestion = sf::seconds(10);
    sf::Time        mTimeLeft;
    int             mQuestionIndex;
    int             mScore;
    int             mCorrectAnswerIndex;
    std::string     mOptionTexts[4];
};