#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

template<typename Resource, typename Identifier>
class ResourceHolder
{
    public:
        void load(Identifier id, const std::string& filename);
        template <typename Parameter>
        void load(Identifier id, const std::string& filename, const Parameter& secondParam);

        Resource& get(Identifier id);
        const Resource& get(Identifier id) const;

    private:
        std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"

namespace Textures
{
    enum ID
    {
        Logo,
        StartingFrameBackground,
        DashboardBackground,
        MenuBackground,
        Footer,
        WoodenBackground1,
        WoodenBackground2,
        NONE
    };  
} 

namespace Fonts
{
    enum ID
    {
        NONE,
        DEFAULT
    };
}

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;