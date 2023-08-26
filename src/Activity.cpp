#include <Activity.hpp>
#include <ActivityStack.hpp>

Activity::Context::Context(sf::RenderWindow& window,
                           TextureHolder& textures,
                           FontHolder& fonts,
                           Json::Value& data,
                           API& api)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, data(&data)
, api(&api)
{
}

Activity::Activity(ActivityStack& stack, Context context, Intent::Ptr intent)
: mStack(&stack)
, mContext(context)
, mIntent(std::move(intent))
{
}

Activity::~Activity()
{
}

void Activity::requestStackPush(int activityID, Intent::Ptr intent)
{
    mStack->pushActivity(activityID, std::move(intent));
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

Activity::Intent* Activity::getIntent()
{
    return mIntent.get();
}