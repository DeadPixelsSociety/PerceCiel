#include <iostream>

#include "map/DirtBlock.h"
#include "Game.h"

int main() {
	std::cout << "Hello World" << std::endl;
	DirtBlock dirtBlock;
	dirtBlock.afficher();

	Game game;
	game.setNextState(GAME_STATE_MENU);
	game.start();

	return 0;
}
