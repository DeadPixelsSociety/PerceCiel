#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "SFML/Graphics.hpp"
#include <map>

class TextureLoader{

    public:
        static TextureLoader* getSingleton();
        ~TextureLoader();
        sf::Texture& loadFromFile(const char* fileName);

    private:
        TextureLoader();
        std::map<const char*, sf::Texture> m_loadedTextures;
        static TextureLoader* m_singleton;

};

#endif
