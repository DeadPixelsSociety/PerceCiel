#ifndef ABSTRACTDRAWABLE_H
#define ABSTRACTDRAWABLE_H

#include "SFML/Graphics.hpp"
#include <vector>

class AbstractDrawable: public sf::Drawable{

    public:
        AbstractDrawable();
        ~AbstractDrawable();
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void initializeDrawables() = 0;

    protected:
        std::vector<const sf::Drawable*> m_drawables;

};

#endif
