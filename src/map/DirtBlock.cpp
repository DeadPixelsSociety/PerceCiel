#include "map/dirtblock.h"
#include <iostream>

	DirtBlock::DirtBlock() : Block(1)
	{
	}

    void DirtBlock::afficher() const {
        std::cout << "DirtBlock : id : "<< std::endl;
    }
