#include <iostream>
#include "graphic/AbstractWindow.h"
#include "events/AbstractKeyboardEventHandler.h"
#include "events/AbstractMouseEventHandler.h"
#include "map/DirtBlock.h"
#include "graphic/AnimatedSprite.h"
#include "graphic/TextureLoader.h"
#include "map/Chunk.h"
#include "tools/MapVisitor.h"
#include <tmx/TMX.h>
#include <tmx/Map.h>
#include <tmx/Base.h>

#include "graphic/TextureBlockManager.h"

using namespace tmx;

class KeyboardEventHandler : public AbstractKeyboardEventHandler {
public:

    KeyboardEventHandler() :
    AbstractKeyboardEventHandler() {
    }

    void onKeyPressed(AbstractWindow* window, sf::Event event) {
        std::cout << "Key pressed" << std::endl;
        if (event.key.code == sf::Keyboard::Escape) {
            window->close();
        }
    }

    void onKeyReleased(AbstractWindow* window, sf::Event event) {
        std::cout << "Key released" << std::endl;
    }

};

class MouseEventHandler : public AbstractMouseEventHandler {
public:

    MouseEventHandler() :
    AbstractMouseEventHandler() {
    }

    void onButtonPressed(AbstractWindow* window, sf::Event event) {
        std::cout << "Mouse pressed !" << std::endl;
    }

    void onButtonReleased(AbstractWindow* window, sf::Event event) {
        std::cout << "Mouse released !" << std::endl;
    }

    void onMoved(AbstractWindow* window, sf::Event event) {
        AnimatedSprite* hero = dynamic_cast<AnimatedSprite*> (window->getDrawableAt(0));
        hero->nextFrame();
        std::cout << "Mouse moved !" << std::endl;
    }

};

int main() {

    // FULLSCREEN WINDOW (EXIT WITH ESCAPE OR MOUSE CLICK)
    // AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), true);

    // NORMAL WINDOW WITH WIDTH 800 AND HEIGHT 600
    AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), false);

    sf::Texture heroTexture = TextureLoader::getSingleton()->loadFromFile("res/hero.png");
    AnimatedSprite hero(heroTexture, sf::IntRect(0, 0, 32, 32));
    hero.addFrame(sf::IntRect(32, 0, 32, 32));
    hero.addFrame(sf::IntRect(64, 0, 32, 32));
    hero.addFrame(sf::IntRect(0, 32, 32, 32));
    hero.addFrame(sf::IntRect(32, 32, 32, 32));
    hero.addFrame(sf::IntRect(64, 32, 32, 32));
    hero.addFrame(sf::IntRect(0, 64, 32, 32));
    hero.addFrame(sf::IntRect(32, 64, 32, 32));
    hero.addFrame(sf::IntRect(64, 64, 32, 32));
    hero.addFrame(sf::IntRect(0, 96, 32, 32));
    hero.addFrame(sf::IntRect(32, 96, 32, 32));
    hero.addFrame(sf::IntRect(64, 96, 32, 32));
    w.addDrawable(hero);

    Chunk chunk;

    Map *map = parseMapFile("shared/PerceCiel/maps/test.tmx");
    MapVisitor visitor(&chunk);
    map->visitLayers(visitor);
    for (auto &tileSet : map->getTileSets()) {
        TextureBlockManager::setTileSet(tileSet);
    }


    chunk.load();
    delete map;

    w.addDrawable(chunk);

    w.show();



    return 0;
}
