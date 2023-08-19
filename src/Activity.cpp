#include <Activity.hpp>
#include <ActivityStack.hpp>

Activity::Context::Context(sf::RenderWindow& window,
                           TextureHolder& textures,
                           FontHolder& fonts,
                           Json::Value& data)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, data(&data)
{
}

Activity::Activity(ActivityStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{
}

Activity::~Activity()
{
}

void Activity::requestStackPush(int activityID)
{
    mStack->pushActivity(activityID);
}

void Activity::requestStackPop()
{
    mStack->popActivity();
}

void Activity::requestActivityClear()
{
    mStack->clearActivities();
}

Activity::Context& Activity::getContext()
{
    return mContext;
}