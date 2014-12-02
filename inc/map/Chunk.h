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

#include <string>
#include <tmx/TileSet.h>

class Chunk : public sf::Drawable {
public:
    enum {chunkSize = 4};
    
    static const std::string saveDir;
//    static const sf::Vector2i vectorSize;
    Chunk(const sf::Vector2i &position = sf::Vector2i(0,0));
    virtual ~Chunk();

    inline short* blocks() {
        return m_blocks;
    }

    inline const short* blocks() const {
        return m_blocks;
    }

    short block(int col, int row) const;
    short& block(int col, int row);
    
//    inline void setTexture(const sf::Texture *texture) { m_texture = texture; }
    std::string getDefaultSavePath();
    
    void loadGraphic();
    void loadFromFile();
    void loadFromFile(const std::string &path);
    void saveInFile();
    void saveInFile(const std::string &path);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


private:
    sf::Vector2i m_position;
    short m_blocks[chunkSize * chunkSize];
    sf::VertexArray m_vertices;
//    const sf::Texture *m_texture;

};

#endif	/* CHUNK_H */

