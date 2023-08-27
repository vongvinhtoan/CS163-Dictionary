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

Activity::Activity(ActivityStack& stack, Context context, Intent::Ptr intent, int requestCode)
: mStack(&stack)
, mContext(context)
, mRequestCode(requestCode)
, mIntent(std::move(intent))
{
}


Activity::~Activity()
{
}

void Activity::onBackActivity(int resultCode, Intent::Ptr intent)
{
}

void Activity::requestStackPush(int activityID, Intent::Ptr intent, int requestCode)
{
    mStack->pushActivity(activityID, std::move(intent), requestCode);
}

void Activity::requestStackPop()
{
    mStack->popActivity();
}

void Activity::requestActivityClear()
{
    mStack->clearActivities();
}

void Activity::requestBackActivity(Intent::Ptr intent)
{
    mStack->backActivity(getRequestCode(), std::move(intent));
}

Activity::Context& Activity::getContext()
{
    return mContext;
}

Activity::Intent* Activity::getIntent()
{
    return mIntent.get();
}

int Activity::getRequestCode()
{
    return mRequestCode;
}