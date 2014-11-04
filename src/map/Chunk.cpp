/* 
 * File:   Chunk.cpp
 * Author: maxence
 * 
 * Created on 26 octobre 2014, 12:27
 */

#include "map/Chunk.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>

#define TILE_SIZE 4

const int Chunk::chunkSize = 64;

Chunk::Chunk() {
    for(int i=0 ; i < chunkSize*chunkSize; ++i)
        m_blocks[i] = 0;
}

Chunk::~Chunk() {
}

short Chunk::block(int col, int row) const {
    return m_blocks[row * chunkSize + col];
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


    int pos = 0;
    for (int ligne = 0; ligne < chunkSize; ++ligne) {
        for (int col = 0; col < chunkSize; ++col) {
            std::cout << m_blocks[pos] << std::endl;
//            if (m_blocks[pos] == 0)
//                continue;

            // get a pointer to the current tile's quad
            sf::Vertex* quad = &m_vertices[pos * 4];

            // define its 4 corners
            quad[0].position = sf::Vector2f(ligne * TILE_SIZE, col * TILE_SIZE);
            quad[1].position = sf::Vector2f((ligne + 1) * TILE_SIZE, col * TILE_SIZE);
            quad[2].position = sf::Vector2f((ligne + 1) * TILE_SIZE, (col + 1) * TILE_SIZE);
            quad[3].position = sf::Vector2f(ligne * TILE_SIZE, (col + 1) * TILE_SIZE);

            quad[0].color = mapColor[m_blocks[pos]]; // + j * width];
            quad[1].color = mapColor[m_blocks[pos]]; // + j * width + 1];
            quad[2].color = mapColor[m_blocks[pos]]; // + (j + 1) * width + 1];
            quad[3].color = mapColor[m_blocks[pos]]; // + (j + 1) * width];

            ++pos;
        }
    }
}

void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_vertices, states);
}
