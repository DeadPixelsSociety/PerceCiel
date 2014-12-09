/* 
 * File:   MapVisitor.cpp
 * Author: maxence
 * 
 * Created on 4 novembre 2014, 18:05
 */

#include "tools/MapVisitor.h"
#include "graphic/TextureLoader.h"
#include "SFML/Graphics/Texture.hpp"
#include "map/ChunkWorld.h"
#include <iostream>

MapVisitor::MapVisitor(ChunkWorld *chunkWorld)
: m_map(chunkWorld) {
}

MapVisitor::~MapVisitor() {
}

void MapVisitor::visitImageLayer(tmx::ImageLayer& layer) {
    std::cout << layer.getName() << std::endl;
    std::cout << "Layer not implement !" << std::endl;
}

void MapVisitor::visitObjectLayer(tmx::ObjectLayer& layer) {
    std::cout << layer.getName() << std::endl;
    std::cout << "Layer not implement !" << std::endl;

}
#include <iostream>
void MapVisitor::visitTileLayer(tmx::TileLayer& layer) {
    std::cout << layer.getName() << std::endl;
    if (!layer.isVisible()) {
        std::cout << "Not visible" << std::endl;
        return;
    }
    
    // @TODO
    std::string widthString = layer.getProperty("width", "2500");
    std::cout << "width " << widthString << std::endl;

    int width = atoi(widthString.c_str());
    unsigned k = 0;
    for (auto cell : layer) {
        unsigned i = k % width;
        unsigned j = k / width;
        //    assert(j < height);
        //    unsigned x = i * tilewidth;
        //    unsigned y = j * tileheight;
        unsigned gid = cell.getGID();
        k++;
        if(gid == 0)
            continue;
        
        sf::Vector2i coordChunk(i/Chunk::chunkSize,j/Chunk::chunkSize);
        Chunk *chunk = m_map->load(coordChunk);
//        std::cout << "id(" << gid << ") chunk(" << coordChunk.x << ":"<< coordChunk.y <<"). pos ( " << i%Chunk::chunkSize << ":"<<j%Chunk::chunkSize << ")"<< std::endl;
        
        chunk->setBlock(i%Chunk::chunkSize, j%Chunk::chunkSize, gid);
//        std::cout << "id(" << chunk->getBlock(i%Chunk::chunkSize, j%Chunk::chunkSize) << ")" << std::endl;
        
//        m_map->release(i,j);
        //    if (gid != 0) {
        //      drawGID(x, y, gid);
        //    }
        
//    std::cout << "test " << widthString << std::endl;
    }
    std::cout << "fin read" << std::endl;
}


