#include <iostream>
#include "graphic/AbstractWindow.h"

AbstractWindow::AbstractWindow(const char* title, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler):
    m_keyboardEventHandler(keyboardEventHandler),
    m_mouseEventHandler(mouseEventHandler),
    m_title(title)
{
}

AbstractWindow::~AbstractWindow(){
    delete m_window;
    delete m_keyboardEventHandler;
    delete m_mouseEventHandler; }

void AbstractWindow::close(){
    m_window->close();
}

void AbstractWindow::show(){
    m_window = new sf::RenderWindow(sf::VideoMode(800, 600), m_title);
    handleEvents();
}

void AbstractWindow::handleEvents(){
    sf::Event event;
    while(m_window->isOpen()){
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
        }
    }
}
