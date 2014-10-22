#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <SFML/Graphics.hpp>
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"

class AbstractWindow{

    public:
        AbstractWindow(const char* title, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler);
        virtual ~AbstractWindow();
        void close();
        void show();

    private:
        AbstractKeyboardEventHandler* m_keyboardEventHandler;
        AbstractMouseEventHandler* m_mouseEventHandler;
        const char* m_title;
        sf::RenderWindow* m_window;
        void handleEvents();

};

#endif
