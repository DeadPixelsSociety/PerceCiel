/* 
 * File:   chunkLoader.h
 * Author: maxence
 *
 * Created on 12 novembre 2014, 19:02
 */

#ifndef CHUNKLOADER_H
#define	CHUNKLOADER_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <iostream>
#include "Chunk.h"
#include "ChunkWorld.h"

class ChunkLoader {
public:
    ChunkLoader(ChunkWorld &chunkWorld, const sf::Vector2i &center = sf::Vector2i(0,0), int size = 4, int limit = 8);
    virtual ~ChunkLoader();
//    Chunk& getChunk(const sf::Vector2i &position);
    void setCenter(sf::Vector2i center);
    
    
private:
    void update();
    void loadChunk(const sf::Vector2i &chunkPosition);
    void deleteOutChunk();
    void deleteBottomLine();
    void deleteLeftColumn();
    void deleteRightColumn();
    void deleteTopLine();
    void addInChunk();
    void growBottom();
    void addLeftColumn();
    void addRightColumn();
    void growTop();
    
private:
    ChunkWorld &m_chunkWorld;
    sf::Vector2i m_center;
    int m_size;
    int m_limit;
    
//    int m_right;
//    int m_left;
//    int m_top;
//    int m_bottom;
    
    sf::Vector2i m_topLeftCorner;
    sf::Vector2i m_bottomRightCorner;
    
};

#endif	/* CHUNKLOADER_H */

