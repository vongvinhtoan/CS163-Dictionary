#pragma once

#include <Activity.hpp>
#include <SFML/Graphics.hpp>
#include <functional>
#include <map>

class ActivityStack
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear
    };

    ActivityStack(Activity::Context context);
    template <typename T>
    void    registerActivity(int activityID);
    void    update(sf::Time dt);
    void    draw();
    void    handleEvent(const sf::Event& event);
    void    handleRealtimeInput();
    void    pushActivity(int activityID);
    void    popActivity();
    void    clearActivities();
    bool    isEmpty() const;

private:
    Activity::Ptr   createActivity(int activityID);
    void            applyPendingChanges();

private:
    struct PendingChange
    {
        PendingChange(Action action, int activityID = 0);
        Action      action;
        int         activityID;
    };

private:
    std::vector<Activity::Ptr>                      mStack;
    std::vector<PendingChange>                      mPendingList;
    Activity::Context                               mContext;
    std::map<int, std::function<Activity::Ptr()>>   mFactories;
};

template <typename T>
void ActivityStack::registerActivity(int activityID)
{
    mFactories[activityID] = [this] ()
    {
        return Activity::Ptr(new T(*this, mContext));
    };
}