#ifndef ABSTRACTKEYBOARDEVENTHANDLER_H
#define ABSTRACTKEYBOARDEVENTHANDLER_H

#include <SFML/Graphics.hpp>
class AbstractWindow;

class AbstractKeyboardEventHandler{

    public:
        AbstractKeyboardEventHandler();
        virtual ~AbstractKeyboardEventHandler();
        virtual void onKeyPressed(AbstractWindow* window, sf::Event event) = 0;
        virtual void onKeyReleased(AbstractWindow* window, sf::Event event) = 0;

};

#endif
