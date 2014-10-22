#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"

class AbstractWindow{

    public:
        AbstractWindow(const char* title, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler);
        virtual ~AbstractWindow();
        void addDrawable(const sf::Drawable& drawable);
        void clear();
        void close();
        void display();
        void redraw();
        void show();

    private:
        AbstractKeyboardEventHandler* m_keyboardEventHandler;
        AbstractMouseEventHandler* m_mouseEventHandler;
        const char* m_title;
        sf::RenderWindow* m_window;
        std::vector<const sf::Drawable*> m_drawables;
        void handleEvents();

};

#endif
