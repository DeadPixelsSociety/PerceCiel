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

class ChunkLoader {
public:
    ChunkLoader(const sf::Vector2i &center = sf::Vector2i(0,0), int space = 4, int size = 8);
    virtual ~ChunkLoader();
    Chunk& getChunk(const sf::Vector2i &position);
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
    sf::Vector2i m_center;
    int m_size;
    int m_space;
    
    sf::Vector2i m_topLeftCorner;
    sf::Vector2i m_bottomRightCorner;
    
    std::unordered_map<int, std::unordered_map<int, Chunk> > m_container;

};

#endif	/* CHUNKLOADER_H */

