#include <ActivityStack.hpp>

ActivityStack::ActivityStack(Activity::Context context)
: mContext(context)
, mFactories()
, mStack()
, mPendingList()
{
}

void ActivityStack::update(sf::Time dt)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->update(dt))
            break;
    }

    applyPendingChanges();
}

void ActivityStack::draw()
{
    for (auto& activity : mStack)
        activity->draw();

    applyPendingChanges();
}

void ActivityStack::handleEvent(const sf::Event& event)
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleEvent(event))
            break;
    }

    applyPendingChanges();
}

void ActivityStack::handleRealtimeInput()
{
    for (auto itr = mStack.rbegin(); itr != mStack.rend(); ++itr)
    {
        if (!(*itr)->handleRealtimeInput())
            break;
    }

    applyPendingChanges();
}

void ActivityStack::pushActivity(int activityID)
{
    mPendingList.push_back(PendingChange(Push, activityID));
}

void ActivityStack::popActivity()
{
    mPendingList.push_back(PendingChange(Pop));
}

void ActivityStack::clearActivities()
{
    mPendingList.push_back(PendingChange(Clear));
}

bool ActivityStack::isEmpty() const
{
    return mStack.empty();
}

Activity::Ptr ActivityStack::createActivity(int activityID)
{
    auto found = mFactories.find(activityID);
    assert(found != std::nullopt);

    return found->second();
}

void ActivityStack::applyPendingChanges()
{
    for (auto& change : mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createActivity(change.activityID));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    }

    mPendingList.clear();
}

ActivityStack::PendingChange::PendingChange(Action action, int activityID)
: action(action)
, activityID(activityID)
{
}