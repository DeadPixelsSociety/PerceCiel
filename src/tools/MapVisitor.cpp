/* 
 * File:   MapVisitor.cpp
 * Author: maxence
 * 
 * Created on 4 novembre 2014, 18:05
 */

#include "tools/MapVisitor.h"
#include "graphic/TextureLoader.h"
#include "SFML/Graphics/Texture.hpp"

MapVisitor::MapVisitor(Chunk *chunk)
: m_chunk(chunk) {
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
    
    
    std::string widthString = layer.getProperty("width", "100");
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
        m_chunk->block(i, j) = gid;
        
        //    if (gid != 0) {
        //      drawGID(x, y, gid);
        //    }
        k++;
        
//    std::cout << "test " << widthString << std::endl;
    }
}


