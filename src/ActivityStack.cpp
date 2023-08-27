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

void ActivityStack::pushActivity(int activityID, Activity::Intent::Ptr intent, int requestCode)
{
    mPendingList.push_back(PendingChange(Push, activityID, std::move(intent), requestCode));
}

void ActivityStack::popActivity()
{
    mPendingList.push_back(PendingChange(Pop));
}

void ActivityStack::clearActivities()
{
    mPendingList.push_back(PendingChange(Clear));
}

void ActivityStack::backActivity(int resultCode, Activity::Intent::Ptr intent)
{
    mPendingList.push_back(PendingChange(BackActivity, 0, std::move(intent), resultCode));
}

bool ActivityStack::isEmpty() const
{
    return mStack.empty();
}

Activity::Ptr ActivityStack::createActivity(int activityID, Activity::Intent::Ptr intent, int requestCode)
{
    auto found = mFactories.find(activityID);
    assert(found != mFactories.end());

    return (found->second)(std::move(intent), requestCode);
}

void ActivityStack::applyPendingChanges()
{
    for (auto& change : mPendingList)
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createActivity(change.activityID, std::move(change.intent), change.requestCode));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;

            case BackActivity:
                if (!mStack.empty())
                    mStack.back()->onBackActivity(change.requestCode, std::move(change.intent));
                break;
        }
    }

    mPendingList.clear();
}

ActivityStack::PendingChange::PendingChange(Action action, int activityID, Activity::Intent::Ptr intent, int requestCode)
: action(action)
, activityID(activityID)
, intent(std::move(intent))
, requestCode(requestCode)
{
}