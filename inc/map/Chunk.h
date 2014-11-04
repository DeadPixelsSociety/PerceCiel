/* 
 * File:   Chunk.h
 * Author: maxence
 *
 * Created on 26 octobre 2014, 12:27
 */

#ifndef CHUNK_H
#define	CHUNK_H

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
//#include <SFML/Graphics/RenderTarget.hpp>
//#include <SFML/Graphics/RenderStates.hpp>

class Chunk : public sf::Drawable {
public:
    static const int chunkSize;
    Chunk();
    virtual ~Chunk();

    inline short* blocks() {
        return m_blocks;
    }

    inline const short* blocks() const {
        return m_blocks;
    }

    short block(int col, int row) const;
    short& block(int col, int row);

    void load();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
    short m_blocks[64 * 64];
    sf::VertexArray m_vertices;

};

#endif	/* CHUNK_H */

