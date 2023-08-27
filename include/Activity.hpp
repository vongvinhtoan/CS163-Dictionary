#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <ResourceHolder.hpp>
#include <json.h>
#include <any>
#include <unordered_map>
#include <Database.hpp>
#include <API.hpp>
#include <iostream>

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
        DICTIONARY,
        FAVORITELIST,
        ADD,
        FAVCONFIRM,
        EDITDEFINITION,
        WORDDELCONFIRM,
        HISTORY,
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
                Json::Value& data,
                API& api);
        sf::RenderWindow*  window;
        TextureHolder*     textures;
        FontHolder*        fonts;
        Json::Value*       data;
        API*               api;
    };

    class Intent
    {
        std::unordered_map<std::string, std::any> mExtras;

    public:
        typedef std::unique_ptr<Intent> Ptr;
        Intent() = default;
        Intent(const Intent&) = default;
        Intent(Intent&&) = default;
        Intent& operator=(const Intent&) = default;
        Intent& operator=(Intent&&) = default;
        ~Intent() = default;

        template<typename T>
        void putExtra(const std::string& key, T value)
        {
            mExtras[key] = value;
        }

        template<typename T>
        T getExtra(const std::string& key)
        {
            auto found = mExtras.find(key);
            if (found == mExtras.end()) {
                std::cout<<"Key not found"<<std::endl;
                throw std::runtime_error("Key not found");
            }
            return std::any_cast<T>(found->second);
        }

        bool hasExtra(const std::string& key)
        {
            auto found = mExtras.find(key);
            if (found == mExtras.end()) {
                return false;
            }
            return true;
        }
    };

                    Activity(ActivityStack& stack, Context context, Intent::Ptr intent = nullptr, int requestCode = 0);
    virtual         ~Activity();
    virtual void    draw() = 0;
    virtual bool    update(sf::Time dt) = 0;
    virtual bool    handleEvent(const sf::Event& event) = 0;
    virtual bool    handleRealtimeInput() = 0;
    virtual void    onBackActivity(int resultCode, Activity::Intent::Ptr intent);
protected: 
    void            requestStackPush(int activityID, Intent::Ptr intent = nullptr, int requestCode = 0);
    void            requestStackPop();
    void            requestActivityClear();
    void            requestBackActivity(Intent::Ptr intent = nullptr);
    Context&        getContext();
    Intent*         getIntent();
    int             getRequestCode();
private:
    ActivityStack*      mStack;
    Context             mContext;
    Intent::Ptr         mIntent;
    int                 mRequestCode;
};