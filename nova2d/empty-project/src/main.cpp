#include "core/Game.h"
#include "scenes/MainMenu.h"
#include "scenes/Level1.h"

int main(int argc, char* argv[])
{
	using namespace emptyproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("Empty Project");

	MainMenu* mainMenu = new MainMenu("mainMenu");
	Level1* level1 = new Level1("level1");

	n2dGameAddScene(mainMenu);
	n2dGameAddScene(level1);

	n2dGameConfigFirstScene(mainMenu);
	
	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}