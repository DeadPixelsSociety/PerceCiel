#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"

#define TICKS_PER_SEC 25
#define SKIP_TICKS 1000 / TICKS_PER_SEC
#define MAX_FRAMESKIP 2

class AbstractWindow{

    public:
        AbstractWindow(const char* title, sf::Vector2i dimensions, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler, bool isFullScreen = false);
        sf::Drawable* getDrawableAt(int index);
        virtual ~AbstractWindow();
        void addDrawable(sf::Drawable& drawable);
        void clear();
        void close();
        void display();
        void redraw();
        void show();

    private:
        AbstractKeyboardEventHandler* m_keyboardEventHandler;
        AbstractMouseEventHandler* m_mouseEventHandler;
        bool m_isFullScreen;
        const char* m_title;
        sf::RenderWindow* m_window;
        sf::Vector2i m_dimensions;
        std::vector<sf::Drawable*> m_drawables;
        void handleEvents();

};

#endif
