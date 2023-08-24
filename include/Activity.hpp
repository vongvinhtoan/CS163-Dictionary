#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <ResourceHolder.hpp>
#include <json.h>
#include <any>
#include <unordered_map>

class ActivityStack;

namespace Activities
{
    enum ID
    {
        DASHBOARD,
        CREDIT,
        GAMEOPTIONS,
        GAMEDEFINITION,
        GAMEDEFINITIONTOUR,
        GAMEWORD,
        GAMEWORDTOUR,
        GAMEOVER,
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

    class Intent
    {
        std::unordered_map<std::string, std::any> mExtras;

    public:
        Intent() = default;
        Intent(const Intent&) = default;
        Intent(Intent&&) = default;
        Intent& operator=(const Intent&) = default;
        Intent& operator=(Intent&&) = default;
        ~Intent() = default;

        template<typename T>
        void putExtra(const std::string& key, T&& value)
        {
            mExtras[key] = std::forward<T>(value);
        }

        template<typename T>
        T getExtra(const std::string& key)
        {
            return std::any_cast<T>(mExtras[key]);
        }
    };

                    Activity(ActivityStack& stack, Context context, Intent intent = Intent());
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
    Intent              mIntent;
};