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
#include "map/ChunkWorld.h"

class MapVisitor : public tmx::LayerVisitor{
public:
    MapVisitor(ChunkWorld *chunkWorld);
    virtual ~MapVisitor();
    

    virtual void visitImageLayer(tmx::ImageLayer& layer); 

    virtual void visitObjectLayer(tmx::ObjectLayer& layer);

    virtual void visitTileLayer(tmx::TileLayer& layer);



private:
    ChunkWorld *m_map;

};

#endif	/* MAPVISITOR_H */

