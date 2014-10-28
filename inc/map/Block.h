#ifndef BLOCK_H
#define BLOCK_H

#include "graphic/AbstractWindow.h"
#include "graphic/AbstractDrawable.h"
#include <vector>

class Block: public AbstractDrawable{

	public:
		Block(short id);
        virtual void initializeDrawables() = 0;

	private:
		short id_block;

};


#endif
