#ifndef ABSTRACTWINDOW_H
#define ABSTRACTWINDOW_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"
#include "tools/Updatable.h"

#define TICKS_PER_SEC 25
#define SKIP_TICKS 1000 / TICKS_PER_SEC
#define MAX_FRAMESKIP 2

class AbstractWindow{

    public:
        AbstractWindow(const char* title, sf::Vector2i dimensions, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler, bool isFullScreen = false);
        sf::Drawable* getDrawableAt(int index);
        virtual ~AbstractWindow();
        void addDrawable(sf::Drawable& drawable);
        void addUpdatable(Updatable& updatable);
        void clear();
        void close();
        void display();
        void redraw();
        void show();
        void setCameraPosition(const sf::Vector2f &position);
        void update(float dt);

    private:
        void handleEvents();
        void checkCollision();
        bool collisionLeft(const sf::FloatRect &hitBox);
        bool collisionRight(const sf::FloatRect &hitBox);
        bool collisionBottom(const sf::FloatRect &hitBox);
        bool collisionTop(const sf::FloatRect &hitBox);
        
        AbstractKeyboardEventHandler* m_keyboardEventHandler;
        AbstractMouseEventHandler* m_mouseEventHandler;
        bool m_isFullScreen;
        const char* m_title;
        sf::RenderWindow* m_window;
        sf::Vector2i m_dimensions;
        std::vector<sf::Drawable*> m_drawables;
        std::vector<Updatable*> m_updatables;
//        std::vector<Character*> m_characters;
        const sf::Vector2f* m_cameraPosition;
//        ChunkWorld *m_world;

};

#endif
