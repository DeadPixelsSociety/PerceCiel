/* 
 * File:   Chunk.cpp
 * Author: maxence
 * 
 * Created on 26 octobre 2014, 12:27
 */

#include "map/Chunk.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

#include "graphic/TextureBlockManager.h"

#define TILE_SIZE 32

//const int Chunk::chunkSize;
//const sf::Vector2i Chunk::vectorSize(128,128);

Chunk::Chunk(const sf::Vector2i &position)
: m_position(position)
{
    for (int i = 0; i < chunkSize * chunkSize; ++i)
        m_blocks[i] = 0;
}

Chunk::~Chunk() {
}

short Chunk::block(int col, int row) const {
    return m_blocks[col + row * chunkSize];
}

short& Chunk::block(int col, int row) {
    return m_blocks[row * chunkSize + col];
}

void Chunk::load() {
    int width = chunkSize;
    int height = chunkSize;
    //    m_vertices.
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(height * width * 4);

    int nbBlock = 10;
    sf::Color mapColor[nbBlock];

    mapColor[0] = sf::Color::Red;
    mapColor[1] = sf::Color::Green;
    mapColor[2] = sf::Color::Magenta;
    mapColor[2] = sf::Color::White;
    
    sf::Vector2f offset(m_position.x * Chunk::chunkSize * TILE_SIZE, m_position.y * Chunk::chunkSize * TILE_SIZE);


    int pos = 0;
    for (int ligne = 0; ligne < chunkSize; ++ligne) {
        for (int col = 0; col < chunkSize; ++col) {
            //            if (m_blocks[pos] == 0)
            //                continue;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[pos * 4];

            // define its 4 corners
            quad[0].position = offset + sf::Vector2f(col * TILE_SIZE, ligne * TILE_SIZE);
            quad[1].position = offset + sf::Vector2f((col + 1) * TILE_SIZE, ligne * TILE_SIZE);
            quad[2].position = offset + sf::Vector2f((col + 1) * TILE_SIZE, (ligne + 1) * TILE_SIZE);
            quad[3].position = offset + sf::Vector2f(col * TILE_SIZE, (ligne + 1) * TILE_SIZE);

//            quad[0].color = mapColor[m_blocks[pos]]; // + j * width];
//            quad[1].color = mapColor[m_blocks[pos]]; // + j * width + 1];
//            quad[2].color = mapColor[m_blocks[pos]]; // + (j + 1) * width + 1];
//            quad[3].color = mapColor[m_blocks[pos]]; // + (j + 1) * width];

            TextureBlockManager::putTextCoords(m_blocks[pos], quad);
//            quad[0].texCoords = sf::Vector2f(0,0);
//            quad[1].texCoords = sf::Vector2f(TILE_SIZE,0);
//            quad[2].texCoords = sf::Vector2f(TILE_SIZE,TILE_SIZE);
//            quad[3].texCoords = sf::Vector2f(0,TILE_SIZE);
            ++pos;
        }
        std::cout << std::endl;
    }
}



void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = TextureBlockManager::s_texture;
    target.draw(m_vertices, states);
}
