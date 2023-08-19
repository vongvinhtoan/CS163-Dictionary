#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <ResourceHolder.hpp>
#include <json.h>

class ActivityStack;

namespace Activities
{
    enum ID
    {
        DASHBOARD,
        MENU
    };
}

class Activity
{
    public:
        typedef std::unique_ptr<Activity> Ptr;
        struct Context 
        {
            Context(sf::RenderWindow& window,
                    TextureHolder& textures,
                    FontHolder& fonts,
                    Json::Value& data);
            sf::RenderWindow*  window;
            TextureHolder*     textures;
            FontHolder*        fonts;
            Json::Value*       data;
        };
                        Activity(ActivityStack& stack, Context context);
        virtual         ~Activity();
        virtual void    draw() = 0;
        virtual bool    update(sf::Time dt) = 0;
        virtual bool    handleEvent(const sf::Event& event) = 0;
        virtual bool    handleRealtimeInput() = 0;
    protected: 
        void            requestStackPush(int activityID);
        void            requestStackPop();
        void            requestActivityClear();
        Context&        getContext();
    private:
        ActivityStack*      mStack;
        Context             mContext;
};