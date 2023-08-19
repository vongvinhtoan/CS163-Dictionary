#include <SceneNode.hpp>
#include <assert.h>
#include <algorithm>

SceneNode::SceneNode(Activity::Context* context)
: mChildren()
, mParent(nullptr)
, mContext(context)
, mIsPressed(false)
{
}

unsigned int SceneNode::getCategory() const
{
    return 0;
}

void SceneNode::attachChild(Ptr child)
{
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), 
    [&] (Ptr& p) -> bool { return p.get() == &node; });

    assert(found != mChildren.end());
    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::clearChildren()
{
    mChildren.clear();
}

int SceneNode::getNumChildren() const
{
    return mChildren.size();
}

SceneNode* SceneNode::getParent() const
{
    return mParent;
}

std::vector<SceneNode*> SceneNode::getChildren() const
{
    std::vector<SceneNode*> children;
    for(const Ptr& child: mChildren)
        children.push_back(child.get());
    return children;
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);

    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const Ptr& child : mChildren)
    {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateCurrent(sf::Time)
{

}

void SceneNode::updateChildren(sf::Time dt)
{
    for(Ptr& child: mChildren)
        child->update(dt);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform = sf::Transform::Identity;

	for (const SceneNode* node = this; node != nullptr; node = node->mParent)
		transform = node->getTransform() * transform;

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    getWorldTransform();
    return getWorldTransform() * sf::Vector2f();
}

int SceneNode::handleEvent(const sf::Event& event, int command)
{
    handleEventChildren(event, command);
    handleEventCurrent(event, command);
    return command;
}

void SceneNode::handleEventCurrent(const sf::Event& event, int& command)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*getContext()->window);
    sf::Vector2f localMousePosition = getWorldTransform().getInverse().transformPoint(mousePosition.x, mousePosition.y);
    
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(contains(localMousePosition))
        {
            if(command & (1<<OnHold))
            {
                mIsPressed = true;
                command &= ~(1<<OnHold);
            }
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased)
    {
        if(contains(localMousePosition))
        {
            if(isPressed())
            {
                mIsPressed = false;
                if(mOnClick && (command & (1<<OnClick)))
                    mOnClick(*this), command &= ~(1<<OnClick);
            }
        }
        mIsPressed = false;
    }
}

void SceneNode::handleEventChildren(const sf::Event& event, int& command)
{
    for(auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
    {
        Ptr &child = *it;
        command &= child->handleEvent(event);
    }
}

int SceneNode::handleRealtimeInput(int command)
{
    handleRealtimeInputChildren(command);
    handleRealtimeInputCurrent(command);
    return command;
}

#include <iostream>

void SceneNode::handleRealtimeInputCurrent(int& command)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*getContext()->window);
    sf::Vector2f localMousePosition = getWorldTransform().getInverse().transformPoint(mousePosition.x, mousePosition.y);

    if(contains(localMousePosition))
    {
        if(isPressed())
        {
            if(mOnHold && (command & (1<<OnHold)))
                mOnHold(*this), command &= ~(1<<OnHold);
        }
        else
        {
            if(mOnHover && (command & (1<<OnHover)))
                mOnHover(*this), command &= ~(1<<OnHover);
        }
    }
    if(!(command & (1<<OnHover)))
        mIsPressed = false;
}

void SceneNode::handleRealtimeInputChildren(int &command)
{
    for(auto it = mChildren.rbegin(); it != mChildren.rend(); ++it)
    {
        Ptr &child = *it;
        command &= child->handleRealtimeInput();
    }
}

void SceneNode::setOnClick(std::function<void(SceneNode&)> onClick)
{
    mOnClick = onClick;
}

void SceneNode::setOnHover(std::function<void(SceneNode&)> onHover)
{
    mOnHover = onHover;
}

void SceneNode::setOnHold(std::function<void(SceneNode&)> onHold)
{
    mOnHold = onHold;
}

Activity::Context* SceneNode::getContext() const
{
    return mContext;
}

sf::FloatRect SceneNode::getLocalBounds() const
{
    return sf::FloatRect();
}

bool SceneNode::isPressed() const
{
    return mIsPressed;
}

bool SceneNode::contains(const sf::Vector2f& point) const
{
    return getLocalBounds().contains(point);
}