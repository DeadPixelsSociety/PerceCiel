/* 
 * File:   MapVisitor.h
 * Author: maxence
 *
 * Created on 4 novembre 2014, 18:05
 */

#ifndef MAPVISITOR_H
#define	MAPVISITOR_H

#include <tmx/LayerVisitor.h>
#include <tmx/ImageLayer.h>
#include <tmx/ObjectLayer.h>
#include <tmx/TileLayer.h>

#include "map/Chunk.h"

class MapVisitor : public tmx::LayerVisitor{
public:
    MapVisitor(Chunk *chunk);
    virtual ~MapVisitor();
    

    virtual void visitImageLayer(tmx::ImageLayer& layer); 

    virtual void visitObjectLayer(tmx::ObjectLayer& layer);

    virtual void visitTileLayer(tmx::TileLayer& layer);



private:
    Chunk *m_chunk;

};

#endif	/* MAPVISITOR_H */

