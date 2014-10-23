#include <iostream>
#include "graphic/AbstractWindow.h"
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"

class KeyboardEventHandler: public AbstractKeyboardEventHandler{

    public:
        KeyboardEventHandler():
            AbstractKeyboardEventHandler()
    {
    }

        void onKeyPressed(AbstractWindow* window, sf::Event event){
            std::cout << "Key pressed" << std::endl;
            if(event.key.code ==sf::Keyboard::Escape){
                window->close();
            }
        }

        void onKeyReleased(AbstractWindow* window, sf::Event event){
            std::cout << "Key released" << std::endl;
        }

};

class MouseEventHandler: public AbstractMouseEventHandler{

    public:
        MouseEventHandler():
            AbstractMouseEventHandler()
    {
    } 
        void onButtonPressed(AbstractWindow* window, sf::Event event){
            std::cout << "Mouse pressed !" << std::endl;
        }

        void onButtonReleased(AbstractWindow* window, sf::Event event){
            std::cout << "Mouse released !" << std::endl;
        }

        void onMoved(AbstractWindow* window, sf::Event event){
            std::cout << "Mouse moved !" << std::endl;
        }

};

int main() {

    // FULLSCREEN WINDOW (EXIT WITH ESCAPE OR MOUSE CLICK)
    // AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), true);

    // NORMAL WINDOW WITH WIDTH 800 AND HEIGHT 600
    AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler());

    // DRAW A RECTANGLE (Width : 100, Height : 100, Color : RED)
    sf::RectangleShape drawable1(sf::Vector2f(100, 100));
    drawable1.setFillColor(sf::Color(255, 0, 0));
    w.addDrawable(drawable1);

    // DRAW A CIRCLE (Radius : 50, Color : GREEN)
    sf::CircleShape drawable2(50);
    drawable2.setFillColor(sf::Color(0, 255, 0));
    w.addDrawable(drawable2);

    w.show();

    return 0;
}
