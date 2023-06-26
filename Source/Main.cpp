#include "Game/Game.h"

// the famous c++ entry point...
int main()
{
	/* We have a 'Game' class so we can keep the main function clean and
	* separate the main game loop from anything else
	*/
	Game::Start();

	return 0;
}