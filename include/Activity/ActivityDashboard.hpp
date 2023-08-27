#pragma once
#include <Activity.hpp>
#include <SceneNode.hpp>
#include <SceneNode\RectangleNode.hpp>
#include <SceneNode\TextNode.hpp>
#include <SceneNode\ButtonNode.hpp>

class ActivityDashboard : public Activity
{
private:
    const float horSpacing = 30.f;
    const float verSpacing = 30.f;
    std::vector<sf::Vector2f> mParticlePositions;
    std::vector<SceneNode*> mParticles;
    sf::Time mParticleTimer;
    const sf::Time mParticleInterval = sf::seconds(1.5f);
    float curve(float t);
    sf::Vector2f lerp(float t);
private:
    enum Layer
    {
        Background,
        Particles,
        DashboardBackground,
        Logo,
        Button,
        Footer,
        LayerCount
    };

    std::unique_ptr<SceneNode> mSceneGraph;
    std::array<SceneNode*, LayerCount> mSceneLayers;

private:
    void   buildScene();

public:
    ActivityDashboard(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode);
    virtual void    draw();
    virtual bool    update(sf::Time dt);
    virtual bool    handleEvent(const sf::Event& event);
    virtual bool    handleRealtimeInput();
};