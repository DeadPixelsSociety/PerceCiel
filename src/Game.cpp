#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "Game.h"

Game::Game() {
	currentState = GAME_STATE_NULL;
	nextState = GAME_STATE_NULL;
}

void Game::clean() {
	//delete m_window;
	//delete m_entity;
}

void Game::mainLoop() {
	sf::RenderWindow m_window(sf::VideoMode(800,600), "PerceCiel - v0.0.0.0.0.1");
	//m_window.setPosition(sf::Vector2i(300, 150));
	m_window.setVerticalSyncEnabled(false);

	sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

	sf::Clock clock;
	int loops;
	float interpolation = 0;

	sf::Int32 nextGameTick = clock.getElapsedTime().asMilliseconds();

	while(currentState != GAME_STATE_EXIT) {
		changeState();

		loops = 0;

		while (clock.getElapsedTime().asMilliseconds() > nextGameTick && loops < MAX_FRAMESKIP) {
            handleEvents(m_window);   // 			=> events manager
            // m_entity->update();			=> update position every tick of the game

            nextGameTick += SKIP_TICKS;
            loops++;
        }

        m_window.clear();
        m_window.draw(shape);
        m_window.display();

        //interpolation = float(clock.getElapsedTime().asMilliseconds() + SKIP_TICKS - nextGameTick) / float(SKIP_TICKS);
        //std::cout << interpolation << std::endl;
        //m_entity.render(interpolation)	=> display window on every frame (with interpolation [might have more fps than ticks/s])
	}

	m_window.close();
	clean();
}

void Game::setNextState(GameStates next) {
	nextState = next;
}

void Game::changeState() {
	currentState = nextState;
	nextState = GAME_STATE_NULL;

	// Gestion des différentes fenetres
	// 		Fenetre de jeu
	// 		Fenetre de menu
	// 		Fenetre de config
}

void Game::handleEvents(sf::RenderWindow &window) {
	sf::Event event;

	while(window.pollEvent(event)) {
		//if(currentState == GAME_STATE_PAUSE)
		//	m_entity.menu_handleEvent(event)	Gestion des event pendant la pause si menu

		switch(event.type) {
			case sf::Event::Closed:
				setNextState(GAME_STATE_EXIT);
				break;

			/*
			case sf::Event::KeyReleased:
				switch(event.key.code) {
					case sf::Keyboard::Escape:
						setNextState(GAME_STATE_PAUSE);

					default:
						break;
				}
				break;
			*/

			default:
				break;
		}
	}
}