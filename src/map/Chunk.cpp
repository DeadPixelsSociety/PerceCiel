/* 
 * File:   Chunk.cpp
 * Author: maxence
 * 
 * Created on 26 octobre 2014, 12:27
 */

#include "map/Chunk.h"
#include "SFML/Graphics/RenderTarget.hpp"
#include <iostream>
#include <fstream>

#include "graphic/TextureBlockManager.h"

#define TILE_SIZE 32

const std::string Chunk::saveDir = "./chunks/";

//const int Chunk::chunkSize;
//const sf::Vector2i Chunk::vectorSize(128,128);

Chunk::Chunk(const sf::Vector2i &position)
: m_position(position) {
    std::cout << "create chunk (" << position.x <<":"<< position.y << ")" << std::endl;
    for (int i = 0; i < chunkSize * chunkSize; ++i)
        m_blocks[i] = 0;
    loadGraphic();
}

Chunk::~Chunk() {
}

short Chunk::getBlock(int col, int row) const {
    return m_blocks[getNumBlock(col,row)];
}

void Chunk::setBlock(int col, int row, int id) {
    int numBlock = getNumBlock(col,row);
    m_blocks[numBlock] = id;
    updateRender(numBlock);
}

std::string Chunk::getDefaultSavePath() {
    return saveDir + std::to_string(m_position.x) + "_" + std::to_string(m_position.y);
}

void Chunk::loadFromFile() {
    return loadFromFile(getDefaultSavePath());
}

void Chunk::loadFromFile(const std::string& path) {
    std::ifstream fichier(path, std::ios::in);
    int indice = 0;
    if (fichier) {
        char c;
        while (fichier.get(c)) {
            m_blocks[indice++] = static_cast<short>(c);
//        std::cout << c;
        }
        std::cout << "lecture effectué" << std::endl;
        fichier.close();
        loadGraphic();

    } else {
//        std::cout << "ouverture impossible pour lecture" << std::endl;
    }
}

void Chunk::saveInFile() {
    saveInFile(getDefaultSavePath());
}

void Chunk::saveInFile(const std::string& path) {
    std::ofstream fichier(path, std::ios::trunc);
    int size = chunkSize * chunkSize;

    if (fichier) {
        for (int i = 0; i < size; ++i) {
            fichier << m_blocks[i];
        }
        fichier.close();

    } else {
        std::cout << "ouverture impossible pour ecriture" << std::endl;
    }
}

void Chunk::loadGraphic() {
    int width = chunkSize;
    int height = chunkSize;
    //    m_vertices.
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(height * width * 4);


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
            
            updateRender(pos);

            //            quad[0].texCoords = sf::Vector2f(0,0);
            //            quad[1].texCoords = sf::Vector2f(TILE_SIZE,0);
            //            quad[2].texCoords = sf::Vector2f(TILE_SIZE,TILE_SIZE);
            //            quad[3].texCoords = sf::Vector2f(0,TILE_SIZE);
            ++pos;
        }
    }
}

void Chunk::updateRender(int blockNum) {
    int nbBlock = 128;
    int blockID = m_blocks[blockNum];
    sf::Color mapColor[nbBlock];

    for(int i = 0; i < 128; ++i)
        mapColor[i] = sf::Color::Red;
//    mapColor[0] = sf::Color::Red;
    mapColor[1] = sf::Color::Green;
    mapColor[2] = sf::Color::Magenta;
    mapColor[3] = sf::Color::White;
    mapColor[13] = sf::Color::White;
    
    sf::Vertex* quad = &m_vertices[blockNum * 4];
//    
//    quad[0].color = mapColor[blockID]; // + j * width];
//    quad[1].color = mapColor[blockID]; // + j * width + 1];
//    quad[2].color = mapColor[blockID]; // + (j + 1) * width + 1];
//    quad[3].color = mapColor[blockID]; // + (j + 1) * width];
//    
    TextureBlockManager::putTextCoords(blockID, quad);
}


void Chunk::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.texture = TextureBlockManager::s_texture;
    target.draw(m_vertices, states);
}
