#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "SFML/Graphics.hpp"
#include <map>

class TextureLoader{

    public:
        static TextureLoader* getSingleton();
        ~TextureLoader();
        sf::Texture& loadFromFile(const std::string & fileName);

    private:
        TextureLoader();
        std::map<const std::string, sf::Texture> m_loadedTextures;
        static TextureLoader* m_singleton;

};

#endif
