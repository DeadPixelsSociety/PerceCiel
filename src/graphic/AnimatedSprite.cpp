#include "graphic/AnimatedSprite.h"
#include "graphic/TextureLoader.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(sf::Texture& texture, sf::IntRect defaultFrame):
    sf::Sprite(),
    m_currentAnimation(NULL),
    m_defaultFrame(defaultFrame)
{
    setTexture(texture);
    setTextureRect(m_defaultFrame);
}

AnimatedSprite::~AnimatedSprite(){
}

void AnimatedSprite::addAnimation(int key, Animation& animation){
        std::cout << "Annimation " << key << " Added" << std::endl;
    m_animations[key] = &animation;
}

void AnimatedSprite::nextFrame(){
    if(m_currentAnimation != NULL){
        m_currentAnimation->nextFrame();
        setTextureRect(m_currentAnimation->getCurrentFrame());
    }else{
        std::cerr << "Error : AnimatedSprite::m_currentAnimation is NULL. You must call AnimatedSprite::selectAnimation(int key) before using AnimatedSprite::nextFrame()." << std::endl;
    }
}

void AnimatedSprite::selectAnimation(int key){
    if(m_animations.find(key) == m_animations.end()){
        std::cerr << "Error : the selected animation \"" << key << "\" does not exist." << std::endl;
    }else{
        m_currentAnimation = m_animations[key];
    }
}

void AnimatedSprite::update(float dt) {

}
