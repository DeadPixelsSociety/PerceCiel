#include "graphic/AbstractDrawable.h"

AbstractDrawable::AbstractDrawable():
    sf::Drawable()
{
}

void AbstractDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(unsigned int i=0; i<m_drawables.size(); i++){
        target.draw(*(m_drawables[i]), states);
    }
}
