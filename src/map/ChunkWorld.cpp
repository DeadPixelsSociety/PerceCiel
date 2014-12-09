/* 
 * File:   ChunkWorld.cpp
 * Author: maxence
 * 
 * Created on 25 novembre 2014, 17:13
 */

#include "map/ChunkWorld.h"

#include <iostream>

ChunkWorld::ChunkWorld() {
}

ChunkWorld::~ChunkWorld() {
}

Chunk* ChunkWorld::load(const sf::Vector2i& chunkPos) {
    auto iterator = m_chunkList[chunkPos.x].find(chunkPos.y);
    
    if(iterator == m_chunkList[chunkPos.x].end()) {
        Chunk *chunk = new Chunk(chunkPos);
        chunk->loadFromFile();
        ChunkCount chunkCount;
        chunkCount.count = 1;
        chunkCount.chunk = chunk;
        m_chunkList[chunkPos.x][chunkPos.y] = chunkCount;
        return chunk;
    }
    else {
        (*iterator).second.count++;
        return (*iterator).second.chunk;
    }
}

void ChunkWorld::release(int i, int j) {
    ChunkCount &chunkCount =  m_chunkList[i][j];
    chunkCount.count--;
    if(chunkCount.count == 0) {
        chunkCount.chunk->saveInFile();
        delete chunkCount.chunk;
        m_chunkList[i].erase(j);
    }
}

void ChunkWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(auto& mapY : m_chunkList) {
        for(auto& chunk : mapY.second) {
            ChunkCount pChunk = chunk.second;
            Chunk &rchunk = *(pChunk.chunk);
            target.draw(rchunk);
        }
    }
}
