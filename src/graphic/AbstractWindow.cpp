#include <iostream>
#include "graphic/AbstractWindow.h"
#include "graphic/AnimatedSprite.h"

AbstractWindow::AbstractWindow(const char* title, sf::Vector2i dimensions, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler, bool isFullScreen):
    m_keyboardEventHandler(keyboardEventHandler),
    m_mouseEventHandler(mouseEventHandler),
    m_isFullScreen(isFullScreen),
    m_title(title),
    m_dimensions(dimensions)
{
    m_window = new sf::RenderWindow();
}

AbstractWindow::~AbstractWindow(){
    delete m_keyboardEventHandler;
    delete m_mouseEventHandler;
}

sf::Drawable* AbstractWindow::getDrawableAt(int index) {
    return m_drawables.at(index);
}

void AbstractWindow::addDrawable(sf::Drawable& drawable){
    m_drawables.push_back(&drawable);
}

void AbstractWindow::clear(){
    m_window->clear();
}

void AbstractWindow::close(){
    m_window->close();
}

void AbstractWindow::display(){
    m_window->display();
}

void AbstractWindow::handleEvents(){
    sf::Event event;

    /*
    while(m_window->isOpen()){
        clear();
        redraw();
        while(m_window->waitEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    close();
                    break;
                case sf::Event::KeyPressed:
                    m_keyboardEventHandler->onKeyPressed(this, event);
                    break;
                case sf::Event::KeyReleased:
                    m_keyboardEventHandler->onKeyReleased(this, event);
                    break;
                case sf::Event::MouseButtonPressed:
                    m_mouseEventHandler->onButtonPressed(this, event);
                    break;
                case sf::Event::MouseButtonReleased:
                    m_mouseEventHandler->onButtonReleased(this, event);
                    break;
                case sf::Event::MouseMoved:
                    m_mouseEventHandler->onMoved(this, event);
                    break;
                default:
                    break;
            }
            clear();
            redraw();
            display();
        }
    }*/
    sf::Clock clock;
    int loops;
    sf::Int32 nextGameTick = clock.getElapsedTime().asMilliseconds();

    /*clear();
    redraw();*/
    while(m_window->isOpen()) {
        loops = 0;

        while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP) {
            nextGameTick += SKIP_TICKS;
            loops++;

                // This update is constant in time and does not depends on computer perf
                // It does, but what can't run an update every 25 sec ?
            while(m_window->pollEvent(event)) {
                // We should m_window->update
                switch(event.type){
                    case sf::Event::Closed:
                        close();
                        break;
                    case sf::Event::KeyPressed:
                        m_keyboardEventHandler->onKeyPressed(this, event);
                        break;
                    case sf::Event::KeyReleased:
                        m_keyboardEventHandler->onKeyReleased(this, event);
                        break;
                    case sf::Event::MouseButtonPressed:
                        m_mouseEventHandler->onButtonPressed(this, event);
                        break;
                    case sf::Event::MouseButtonReleased:
                        m_mouseEventHandler->onButtonReleased(this, event);
                        break;
                    case sf::Event::MouseMoved:
                        m_mouseEventHandler->onMoved(this, event);
                        break;
                    default:
                        break;
                }
            }
        }

        //interpolation = float(clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
        //m_window->redraw(interpolation)
        //  { m_drawables[0].setX(m_drawables[0].getX + interpolation); ...}
        clear();
        redraw();
        display();

        // In-between we update "fake" position aka position with interpolation (percentage of 2 true positions)
        /*
            for example we have 10 display update for a game update:
            pos_x = 0; // Entity x position
            pos_render_x = 0    // RectangleShape x position (or other drawable object)
            first game update pos_x += 10;  // Entity shift on the right
                first display update pos_render_x = 1;  // pos_render_x is just the display of the object not the "real" object
                2nd display update pos_render_x = 2;
                ...
                10th display update pos_render_x = 10;
            2 game update pos_x += 10;
                etc.
            etc.

            The time between 2 game update should be constant, no matter what (except with real crappy pc/coding)
            but the time between 2 display update may not be constant. Interpolation is calculated with real time.
        */
        
    }
}

void AbstractWindow::redraw(){
    for(unsigned int i=0; i<m_drawables.size(); i++){
        m_window->draw(*(m_drawables[i]));
    }
}

void AbstractWindow::show(){
    m_window->create(sf::VideoMode(m_dimensions.x, m_dimensions.y), m_title, m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    handleEvents();
}
