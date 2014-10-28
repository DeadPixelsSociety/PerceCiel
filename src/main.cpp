#include <iostream>
#include "graphic/AbstractWindow.h"
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"
#include "map/DirtBlock.h"
//#include "graphic/AnimatedSprite.h"

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
    AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), false);

    DirtBlock dirt;
    w.addDrawable(dirt);

    w.show();

    return 0;
}
