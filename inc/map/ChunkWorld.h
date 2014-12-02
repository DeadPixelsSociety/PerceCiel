/* 
 * File:   ChunkWorld.h
 * Author: maxence
 *
 * Created on 25 novembre 2014, 17:13
 */

#ifndef CHUNKWORLD_H
#define	CHUNKWORLD_H

#include <map>
#include <unordered_map>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "Chunk.h"

class ChunkCount{
public :
    Chunk* chunk;
    int count;
};

class ChunkWorld : public sf::Drawable {
public:
    ChunkWorld();
    virtual ~ChunkWorld();
    
    Chunk* load(const sf::Vector2i &chunkPos);
    void release(int i, int j);
    inline void release(const sf::Vector2i &chunkPos) { release(chunkPos.x, chunkPos.y); }
    

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
private:
    std::unordered_map<int, std::unordered_map<int, ChunkCount> > m_chunkList;

};

#endif	/* CHUNKWORLD_H */

