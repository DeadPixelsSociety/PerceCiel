#include "graphic/AnimatedSprite.h"
#include "graphic/TextureLoader.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(sf::Texture& texture, sf::IntRect firstFrame):
    sf::Sprite(),
    m_currentFrameIndex(0)
{
    setTexture(texture);
    m_frames.push_back(firstFrame);
    nextFrame();
}

AnimatedSprite::~AnimatedSprite(){
}

void AnimatedSprite::addFrame(const sf::IntRect textureRect){
    m_frames.push_back(textureRect);
}

void AnimatedSprite::nextFrame(){
    setTextureRect(m_frames[m_currentFrameIndex]);
    m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}
