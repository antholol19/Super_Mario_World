#include "Game.h"

int main(int argc, char* argv[])
{
	Game game = Game();
	game.initialize();

	if (game.isRunning())
	{
		game.loop();
	}
	game.shutDown();

	return 0;
}