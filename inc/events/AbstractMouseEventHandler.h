#ifndef ABSTRACTMOUSEEVENTHANDLER_H
#define ABSTRACTMOUSEEVENTHANDLER_H

#include <SFML/Graphics.hpp>
class AbstractWindow;

class AbstractMouseEventHandler{

    public:
        AbstractMouseEventHandler();
        virtual ~AbstractMouseEventHandler();
        virtual void onButtonPressed(AbstractWindow* window, sf::Event event) = 0;
        virtual void onButtonReleased(AbstractWindow* window, sf::Event event) = 0;
        virtual void onMoved(AbstractWindow* window, sf::Event event) = 0;

};

#endif
