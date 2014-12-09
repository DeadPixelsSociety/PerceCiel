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
#include "map/ChunkLoader.h"

class KeyboardEventHandler : public AbstractKeyboardEventHandler {
public:

    KeyboardEventHandler() :
    AbstractKeyboardEventHandler() {
    }

        void onKeyPressed(AbstractWindow* window, sf::Event event){
            if(event.key.code == sf::Keyboard::Escape){
                    window->close();
            }else{
                AnimatedSprite* hero = dynamic_cast<AnimatedSprite*>(window->getDrawableAt(1));
                hero->selectAnimation(event.key.code);
                hero->nextFrame();
                if(event.key.code == sf::Keyboard::S){
                    hero->move(0, 5);
                }else if(event.key.code == sf::Keyboard::Q){
                    hero->move(-5, 0);
                }else if(event.key.code == sf::Keyboard::D){
                    hero->move(5, 0);
                }else if(event.key.code == sf::Keyboard::Z){
                    hero->move(0, -5);
                }
            }
        }

        void onKeyReleased(AbstractWindow* window, sf::Event event){
        }

};

class MouseEventHandler : public AbstractMouseEventHandler {
public:

    MouseEventHandler() :
    AbstractMouseEventHandler() {
    }

        void onButtonPressed(AbstractWindow* window, sf::Event event){
        }

        void onButtonReleased(AbstractWindow* window, sf::Event event){
        }

        void onMoved(AbstractWindow* window, sf::Event event){
        }

};

int main() {

    // FULLSCREEN WINDOW (EXIT WITH ESCAPE OR MOUSE CLICK)
    // AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), true);

    // NORMAL WINDOW WITH WIDTH 800 AND HEIGHT 600
    AbstractWindow w("Hello Window !", sf::Vector2i(800, 600), new KeyboardEventHandler(), new MouseEventHandler(), false);

    sf::Texture heroTexture = TextureLoader::getSingleton()->loadFromFile("res/mayaRight.png");
//    AnimatedSprite hero(heroTexture, sf::IntRect(0, 64, 32, 32));
    AnimatedSprite hero(heroTexture, sf::IntRect(0, 0, 128, 256));

    Animation animationDown(sf::IntRect(0, 0, 32, 32));
    animationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    animationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    animationDown.addFrame(sf::IntRect(32, 0, 32, 32));

    Animation animationLeft(sf::IntRect(0, 32, 32, 32));
    animationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    animationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    animationLeft.addFrame(sf::IntRect(32, 32, 32, 32));

//    Animation animationRight(sf::IntRect(0, 64, 32, 32));
//    animationRight.addFrame(sf::IntRect(32, 64, 32, 32));
//    animationRight.addFrame(sf::IntRect(64, 64, 32, 32));
//    animationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    Animation animationRight(sf::IntRect(0, 0, 256, 160));
    int nbFrames = 12;
    int size = nbFrames * 128;
    for(int i = 0; i < size; i+=128)
        animationRight.addFrame(sf::IntRect(i, 0, 128, 256));

    Animation animationUp(sf::IntRect(0, 96, 32, 32));
    animationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    animationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    animationUp.addFrame(sf::IntRect(32, 96, 32, 32));

//    hero.addAnimation(sf::Keyboard::S, animationDown);
//    hero.addAnimation(sf::Keyboard::Q, animationLeft);
    hero.addAnimation(sf::Keyboard::D, animationRight);
//    hero.addAnimation(sf::Keyboard::Z, animationUp);
    Chunk chunk;

    tmx::Map *map = tmx::parseMapFile("shared/PerceCiel/maps/MapBasic.tmx");
    for (auto &tileSet : map->getTileSets()) {
        TextureBlockManager::setTileSet(tileSet);
    }


    ChunkWorld world;
//    ChunkLoader chunkLoader(world);
    
    MapVisitor visitor(&world);
    map->visitLayers(visitor);
    

//    Chunk c = chunkLoader.getChunk(sf::Vector2i(0,0));
//    c.block(0,0) = 1;
//    c.block(0,1) = 1;
//    c.loadGraphic();
//    Chunk c2 = chunkLoader.getChunk(sf::Vector2i(0,1));
//    c2.block(0,0) = 1;
//    c2.loadGraphic();
//    c2.t
    
//    chunk.load();

    w.addDrawable(world);
//    w.addDrawable(c2);
    w.addDrawable(hero);


    hero.setPosition(6000,6000);
    w.setCameraPosition(hero.getPosition());
    w.show();

    delete map;


    return 0;
}
