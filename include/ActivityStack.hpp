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
        Clear,
        BackActivity
    };

    ActivityStack(Activity::Context context);
    template <typename T>
    void    registerActivity(int activityID);
    void    update(sf::Time dt);
    void    draw();
    void    handleEvent(const sf::Event& event);
    void    handleRealtimeInput();
    void    pushActivity(int activityID, Activity::Intent::Ptr intent = nullptr, int requestCode = 0);
    void    popActivity();
    void    clearActivities();
    void    backActivity(int resultCode, Activity::Intent::Ptr intent = nullptr);
    bool    isEmpty() const;

private:
    Activity::Ptr   createActivity(int activityID, Activity::Intent::Ptr intent, int requestCode);
    void            applyPendingChanges();

private:
    struct PendingChange
    {
        PendingChange(Action action, int activityID = 0, Activity::Intent::Ptr intent = nullptr, int requestCode = 0);
        Action                  action;
        int                     activityID;
        Activity::Intent::Ptr   intent;
        int                     requestCode;
    };

private:
    std::vector<Activity::Ptr>                                                  mStack;
    std::vector<PendingChange>                                                  mPendingList;
    Activity::Context                                                           mContext;
    std::map<int, std::function<Activity::Ptr(Activity::Intent::Ptr, int)>>     mFactories;
};

template <typename T>
void ActivityStack::registerActivity(int activityID)
{
    mFactories[activityID] = [this] (Activity::Intent::Ptr intent = nullptr, int requestCode = 0)
    {
        return Activity::Ptr(new T(*this, mContext, std::move(intent), requestCode));
    };
}