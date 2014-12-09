#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "SFML/Graphics.hpp"
#include "graphic/Animation.h"
#include "tools/Updatable.h"

class AnimatedSprite : public sf::Sprite, public Updatable {
public:
    AnimatedSprite(sf::Texture& texture, sf::IntRect defaultFrame);
    virtual ~AnimatedSprite();
    void addAnimation(int key, Animation& animation);
    void nextFrame();
    void selectAnimation(int key);

    virtual void update(float dt);


private:
    Animation* m_currentAnimation;
    sf::IntRect m_defaultFrame;
    std::map<int, Animation*> m_animations;

};

#endif
