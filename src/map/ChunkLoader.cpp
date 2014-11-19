/* 
 * File:   chunkLoader.cpp
 * Author: maxence
 * 
 * Created on 12 novembre 2014, 19:02
 */

#include "map/ChunkLoader.h"
#include <iostream>

ChunkLoader::ChunkLoader(const sf::Vector2i &center, int space, int size)
: m_center(center), m_space(space), m_size(size), m_topLeftCorner(center), m_bottomRightCorner(center) {
    loadChunk(center);
    update();
}

ChunkLoader::~ChunkLoader() {
}

Chunk& ChunkLoader::getChunk(const sf::Vector2i& position) {
//    auto it = m_container[position.x].emplace(position.y, position).first;
//    return (*it).second;
    return m_container[position.x].at(position.y);
}

void ChunkLoader::setCenter(sf::Vector2i center) {
    m_center = center;
    update();
}

void ChunkLoader::update() {
    std::cout << "update call" << std::endl;
    deleteOutChunk();
    addInChunk();

}

void ChunkLoader::deleteOutChunk() {

    sf::Vector2i diffTL = m_center - m_topLeftCorner;
    if (diffTL.x > m_space) {
    std::cout << "delete tlx" << std::endl;
        for (int i = 0; i < diffTL.x - m_space; ++i)
            deleteLeftColumn();
    }
    if (diffTL.y > m_space) {
    std::cout << "delete tly" << std::endl;
        for (int i = 0; i < diffTL.y - m_space; ++i)
            deleteTopLine();
    }
    sf::Vector2i diffBR = m_bottomRightCorner - m_center;
    if (diffBR.x > m_space) {
    std::cout << "delete brx" << std::endl;
        for (int i = 0; i < diffBR.x - m_space; ++i)
            deleteRightColumn();
    }
    if (diffBR.y > m_space) {
    std::cout << "delete bry" << std::endl;
        for (int i = 0; i < diffBR.y - m_space; ++i)
            deleteBottomLine();
    }
}

void ChunkLoader::deleteRightColumn() {
    // @TODO save in file
    m_container.erase(m_bottomRightCorner.x);
    --m_bottomRightCorner.x;
}

void ChunkLoader::deleteLeftColumn() {
    // @TODO save in file
    m_container.erase(m_topLeftCorner.x);
    ++m_topLeftCorner.x;
}

void ChunkLoader::deleteBottomLine() {
    // @TODO save in file
    for (int i = m_topLeftCorner.x; i < m_bottomRightCorner.x; ++i) {
        m_container[i].erase(m_topLeftCorner.y);
    }
    --m_topLeftCorner.y;
}

void ChunkLoader::deleteTopLine() {
    // @TODO save in file
    for (int i = m_topLeftCorner.x; i < m_bottomRightCorner.x; ++i) {
        m_container[i].erase(m_topLeftCorner.y);
    }
    --m_topLeftCorner.y;
}

void ChunkLoader::addInChunk() {

    sf::Vector2i diffTL = m_center - m_topLeftCorner;
    if (diffTL.x < m_size) {
     std::cout << "add tlx" << std::endl;
       for (int i = 0; i < m_size - diffTL.x; ++i)
            addLeftColumn();
    }
    if (diffTL.y < m_size) {
     std::cout << "add tly" << std::endl;
        for (int i = 0; i < m_size - diffTL.y; ++i)
            growTop();
    }
    sf::Vector2i diffBR = m_bottomRightCorner - m_center;
    if (diffBR.x < m_size) {
      std::cout << "add brx" << std::endl;
       for (int i = 0; i < m_size - diffBR.x; ++i)
            addRightColumn();
    }
    if (diffBR.y < m_size) {
     std::cout << "add bry" << std::endl;
        for (int i = 0; i < m_size - diffBR.y; ++i)
            growBottom();
    }
}

void ChunkLoader::addRightColumn() {
    // @TODO save in file
    ++m_bottomRightCorner.x;
    for (int j = m_topLeftCorner.y; j < m_bottomRightCorner.y; ++j)
        loadChunk(sf::Vector2i(m_bottomRightCorner.x, j));
}

void ChunkLoader::addLeftColumn() {
    // @TODO save in file
    --m_topLeftCorner.x;
    for (int j = m_topLeftCorner.y; j < m_bottomRightCorner.y; ++j)
        loadChunk(sf::Vector2i(m_topLeftCorner.x, j));
}

void ChunkLoader::growBottom() {
    // @TODO save in file
    ++m_bottomRightCorner.y;
    for (int i = m_topLeftCorner.x; i < m_bottomRightCorner.x; ++i)
        loadChunk(sf::Vector2i(i, m_bottomRightCorner.y));
}

void ChunkLoader::growTop() {
    // @TODO save in file
    --m_topLeftCorner.y;
    for (int i = m_topLeftCorner.x; i < m_bottomRightCorner.x; ++i)
        loadChunk(sf::Vector2i(i, m_topLeftCorner.y));
}

void ChunkLoader::loadChunk(const sf::Vector2i &chunkPosition) {
    // @TODO load from file
    m_container[chunkPosition.x].emplace(chunkPosition.y, chunkPosition);
}