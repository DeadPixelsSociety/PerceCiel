/* 
 * File:   TextureBlockManager.h
 * Author: maxence
 *
 * Created on 4 novembre 2014, 22:48
 */

#ifndef TEXTUREBLOCKMANAGER_H
#define	TEXTUREBLOCKMANAGER_H

#include "TextureLoader.h"

class TextureBlockManager {
public:
    TextureBlockManager();
    virtual ~TextureBlockManager();
    
    static void setTileSet(tmx::TileSet const *tileSet);
    static void putTextCoords(short id, sf::Vertex vertices[4]);
public:
    static const sf::Texture* s_texture;
    static const tmx::TileSet* s_tileSet;
    
//    void setBlockTexturePath(const tmx::TileSet &tileSet);
//    void setTextCoords(short id, sf::Vertex vertices[4]);
    
private:
//    tmx::TileSet *m_tileSet;
//    std::string m_texturePath;

};

#endif	/* TEXTUREBLOCKMANAGER_H */

