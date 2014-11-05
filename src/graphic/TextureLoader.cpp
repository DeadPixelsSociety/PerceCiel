#include "graphic/TextureLoader.h"
#include <iostream>

TextureLoader* TextureLoader::m_singleton = NULL;

TextureLoader* TextureLoader::getSingleton(){
    if(TextureLoader::m_singleton == NULL){
        TextureLoader::m_singleton = new TextureLoader();
    }
    return TextureLoader::m_singleton;
}

TextureLoader::TextureLoader(){
}

TextureLoader::~TextureLoader(){
    delete TextureLoader::m_singleton;
}

sf::Texture& TextureLoader::loadFromFile(const std::string &fileName){
    if(m_loadedTextures.find(fileName) == m_loadedTextures.end()){
        m_loadedTextures[fileName] = sf::Texture();
        if(!m_loadedTextures[fileName].loadFromFile(fileName)){
            std::cerr << "Unable to load texture file \"" << fileName << "\"." << std::endl;
        }
    }
    return m_loadedTextures[fileName];
}

