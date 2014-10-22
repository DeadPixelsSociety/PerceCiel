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

    AbstractWindow w("Hello Window !", new KeyboardEventHandler(), new MouseEventHandler());
    w.show();

	return 0;
}
