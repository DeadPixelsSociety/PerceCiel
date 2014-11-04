#include "graphic/Animation.h"

Animation::Animation(sf::IntRect firstFrame):
    m_currentFrameIndex(0)
{
    m_frames.push_back(firstFrame);
}

Animation::~Animation(){
}

sf::IntRect Animation::getCurrentFrame(){
    return m_frames[m_currentFrameIndex];
}

void Animation::addFrame(sf::IntRect frame){
    m_frames.push_back(frame);
}

void Animation::nextFrame(){
    m_currentFrameIndex = (m_currentFrameIndex + 1) % m_frames.size();
}
