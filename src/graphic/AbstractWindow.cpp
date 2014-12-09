#include <iostream>
#include "graphic/AbstractWindow.h"
#include "graphic/AnimatedSprite.h"
#include "map/ChunkWorld.h"

AbstractWindow::AbstractWindow(const char* title, sf::Vector2i dimensions, AbstractKeyboardEventHandler* keyboardEventHandler, AbstractMouseEventHandler* mouseEventHandler, bool isFullScreen):
    m_keyboardEventHandler(keyboardEventHandler),
    m_mouseEventHandler(mouseEventHandler),
    m_isFullScreen(isFullScreen),
    m_title(title),
    m_dimensions(dimensions)
{
    m_window = new sf::RenderWindow();
}

AbstractWindow::~AbstractWindow(){
    delete m_keyboardEventHandler;
    delete m_mouseEventHandler;
}

sf::Drawable* AbstractWindow::getDrawableAt(int index) {
    return m_drawables.at(index);
}

void AbstractWindow::addDrawable(sf::Drawable& drawable){
    m_drawables.push_back(&drawable);
}

void AbstractWindow::addUpdatable(Updatable& updatable){
    m_updatables.push_back(&updatable);
}

void AbstractWindow::clear(){
    m_window->clear();
}

void AbstractWindow::close(){
    m_window->close();
}

void AbstractWindow::display(){
    m_window->display();
}

void AbstractWindow::handleEvents(){
    sf::Event event;

    /*
    while(m_window->isOpen()){
        clear();
        redraw();
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
            clear();
            redraw();
            display();
        }
    }*/
    sf::Clock clock;
    int loops;
    sf::Int32 nextGameTick = clock.getElapsedTime().asMilliseconds();

        sf::View view(m_window->getView());
        view.setCenter(*m_cameraPosition);
        view.zoom(1.0f);
        m_window->setView(view);
//    view.zoom(2.0f);
    /*clear();
    redraw();*/
    while(m_window->isOpen()) {
        loops = 0;

        while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP) {
            nextGameTick += SKIP_TICKS;
            loops++;

                // This update is constant in time and does not depends on computer perf
                // It does, but what can't run an update every 25 sec ?
            while(m_window->pollEvent(event)) {
                // We should m_window->update
                switch(event.type){
                    case sf::Event::Closed:
                        // @TODO save game and chunks
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

        //interpolation = float(clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
        //m_window->redraw(interpolation)
        //  { m_drawables[0].setX(m_drawables[0].getX + interpolation); ...}
        clear();
        update(clock.getElapsedTime().asSeconds());
        
        sf::View view(m_window->getView());
        view.setCenter(*m_cameraPosition);
//        view.sezoom(3.0f);
        m_window->setView(view);
        
        redraw();
        display();

        // In-between we update "fake" position aka position with interpolation (percentage of 2 true positions)
        /*
            for example we have 10 display update for a game update:
            pos_x = 0; // Entity x position
            pos_render_x = 0    // RectangleShape x position (or other drawable object)
            first game update pos_x += 10;  // Entity shift on the right
                first display update pos_render_x = 1;  // pos_render_x is just the display of the object not the "real" object
                2nd display update pos_render_x = 2;
                ...
                10th display update pos_render_x = 10;
            2 game update pos_x += 10;
                etc.
            etc.

            The time between 2 game update should be constant, no matter what (except with real crappy pc/coding)
            but the time between 2 display update may not be constant. Interpolation is calculated with real time.
        */
        
    }
}

void AbstractWindow::redraw(){
    for(unsigned int i=0; i<m_drawables.size(); i++){
        m_window->draw(*(m_drawables[i]));
    }
}

void AbstractWindow::show(){
    m_window->create(sf::VideoMode(m_dimensions.x, m_dimensions.y), m_title, m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default);
    handleEvents();
}

void AbstractWindow::setCameraPosition(const sf::Vector2f &position) {
    m_cameraPosition = &position;
}

void AbstractWindow::update(float dt) {
    for (auto entity : m_updatables) {
        entity->update(dt);
    }

}

void AbstractWindow::checkCollision() {
//    for(auto* character : m_characters) {
//        if(character.collisionWallEnable()) {
//            const sf::FloatRect &hitBox = character.hitBox();
//            m_world->getBox(hitBox., hitBox.)
//            float 
//        }
//    }
}

bool AbstractWindow::collisionBottom(const sf::FloatRect& hitBox) {
//    return containsColliableBox(hitBox)
}



