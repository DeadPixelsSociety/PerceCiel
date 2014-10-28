#include "map/DirtBlock.h"
#include <iostream>

DirtBlock::DirtBlock():
    Block(1)
{
    initializeDrawables();
}

void DirtBlock::initializeDrawables(){
    m_drawables.push_back(new sf::RectangleShape(sf::Vector2f(25, 25)));
}
