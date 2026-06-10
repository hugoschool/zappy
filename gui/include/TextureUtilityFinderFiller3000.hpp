#pragma once

#include <Texture.hpp>
#include <map>
namespace zappy {
    // Texture Utility Finder Filler 3000
    class TUFF {
        public:
            TUFF();
            ~TUFF();

            static void getMaterialsTextures(std::map<int, raylib::Texture2D>&, std::string);
    };
}