#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>
#include <Activity.hpp>

class SceneNode : 
public sf::Drawable,
public sf::Transformable,
private sf::NonCopyable
{
public:
    typedef std::unique_ptr<SceneNode> Ptr;

public:
                            SceneNode(Activity::Context* context);
    void                    attachChild(Ptr child);
    Ptr                     detachChild(const SceneNode& node);
    void                    clearChildren();
    int                     getNumChildren() const;
    SceneNode*              getParent() const;
    std::vector<SceneNode*> getChildren() const;
    void                    update(sf::Time dt);
    sf::Vector2f            getWorldPosition() const;
    sf::Transform           getWorldTransform() const;
    virtual unsigned int    getCategory() const;
    int                     handleRealtimeInput(int command = (1 << CommandCount) - 1);
    int                     handleEvent(const sf::Event& event, int command = (1 << CommandCount) - 1);
    void                    setOnClick(std::function<void(SceneNode&)> onClick);
    void                    setOnHover(std::function<void(SceneNode&)> onHover);
    void                    setOnHold(std::function<void(SceneNode&)> onHold);
    void                    setOnLostHover(std::function<void(SceneNode&)> onLostHover);
    virtual sf::FloatRect   getLocalBounds() const;
    bool                    isPressed() const;
    void                    enable();
    void                    disable();
    bool                    isEnabled() const;

protected:
    virtual void        draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void        drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void        drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void        updateCurrent(sf::Time dt);
    void                updateChildren(sf::Time dt);
    virtual void        handleEventCurrent(const sf::Event& event, int& command);
    void                handleEventChildren(const sf::Event& event, int& command);
    virtual void        handleRealtimeInputCurrent(int& command);
    void                handleRealtimeInputChildren(int& command);
    Activity::Context*  getContext() const;

protected:
    enum Command
    {
        OnClick,
        OnHover,
        OnHold,
        CommandCount
    };

protected:
    bool                            mIsEnabled;
    Activity::Context*              mContext;
    std::vector<Ptr>                mChildren;
    SceneNode*                      mParent;
    bool                            mIsPressed;
    std::function<void(SceneNode&)> mOnClick;
    std::function<void(SceneNode&)> mOnHover;
    std::function<void(SceneNode&)> mOnLostHover;
    std::function<void(SceneNode&)> mOnHold;
    virtual bool                    contains(const sf::Vector2f& point) const;
};

