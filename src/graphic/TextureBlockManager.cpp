/* 
 * File:   TextureBlockManager.cpp
 * Author: maxence
 * 
 * Created on 4 novembre 2014, 22:48
 */

#include <tmx/TileSet.h>

#include "graphic/TextureBlockManager.h"
#include <iostream>

TextureBlockManager::TextureBlockManager() {
}

TextureBlockManager::~TextureBlockManager() {
}
const sf::Texture* TextureBlockManager::s_texture = NULL;
const tmx::TileSet* TextureBlockManager::s_tileSet = NULL;

void TextureBlockManager::putTextCoords(short id, sf::Vertex vertices[4]) {
    if(id == 0)
        return;
    int uid = id - s_tileSet->getFirstGID();
    auto rect = s_tileSet->getCoords(uid, TextureBlockManager::s_tileSet->getImage()->getSize());
//    vertices[0].texCoords = sf::Vector2f(0, 0);
//    vertices[1].texCoords = sf::Vector2f(32, 0);
//    vertices[2].texCoords = sf::Vector2f(32, 32);
//    vertices[3].texCoords = sf::Vector2f(0, 32);
    vertices[0].texCoords = sf::Vector2f(rect.x, rect.y);
    vertices[1].texCoords = sf::Vector2f(rect.x + rect.width, rect.y);
    vertices[2].texCoords = sf::Vector2f(rect.x + rect.width, rect.y + rect.height);
    vertices[3].texCoords = sf::Vector2f(rect.x, rect.y + rect.height);
}

void TextureBlockManager::setTileSet(tmx::TileSet const * tileSet) {
    s_tileSet = tileSet;
    s_texture = &TextureLoader::getSingleton()->loadFromFile(tileSet->getImage()->getSource().generic_string());
}

//void TextureBlockManager::setBlockTexturePath(const tmx::TileSet &tileSet) {
//    m_tileSet = &tileSet;
//    s_texture = TextureLoader::getSingleton()->loadFromFile(tileSet.getImage()->getSource());
//    assert(s_texture != null);
//}

