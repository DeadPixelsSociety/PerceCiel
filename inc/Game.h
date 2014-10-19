#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#define TICKS_PER_SEC 25	// This is game speed, fps is independent
#define SKIP_TICKS 1000 / TICKS_PER_SEC
#define MAX_FRAMESKIP 5


enum GameStates {
    GAME_STATE_NULL,
    GAME_STATE_INTRO,
    GAME_STATE_MENU,
    GAME_STATE_OPTIONS,
    GAME_STATE_GAME,
    GAME_STATE_PAUSE,
    GAME_STATE_EXIT
};


class Game {
public:
	Game();
	void start() { mainLoop(); };
	void setNextState(GameStates next);

protected:
	void handleEvents();
	void mainLoop();
	void changeState();
	void clean();

	sf::RenderWindow m_window;
	GameStates currentState;
	GameStates nextState;
	//Entity_manager m_entity
};

#endif