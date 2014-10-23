#include <iostream>
#include "graphic/AbstractWindow.h"

AbstractWindow::AbstractWindow(const char* title, sf::Vector2i dimensions, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler, bool isFullScreen):
    m_keyboardEventHandler(keyboardEventHandler),
    m_mouseEventHandler(mouseEventHandler),
    m_isFullScreen(isFullScreen),
    m_title(title),
    m_dimensions(dimensions)
{
}

AbstractWindow::~AbstractWindow(){
    delete m_keyboardEventHandler;
    delete m_mouseEventHandler;
}

void AbstractWindow::addDrawable(const sf::Drawable& drawable){
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
    while(m_window->isOpen()){
        clear();
        redraw();
        display();
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
    }
}

void AbstractWindow::redraw(){
    for(unsigned int i=0; i<m_drawables.size(); i++){
        m_window->draw(*(m_drawables[i]));
    }
}

void AbstractWindow::show(){
    m_window = new sf::RenderWindow(sf::VideoMode(m_dimensions.x, m_dimensions.y), m_title, m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Resize);
    handleEvents();
}
