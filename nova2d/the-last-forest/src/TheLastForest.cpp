#include "core/Game.h"
#include "scenes/AllScenes.h"
#include "scenes/level1/LevelOne.h"

int main(int argc, char* argv[])
{
	using namespace thelastforest::scenes;
	using namespace novazero::core;

	// Game Config
	Game game("The Last Forest");
	game.ConfigureDebugOverlay(true);
	n2dSetBackgroundColor("purple");

	n2dAddColor("highlight", "ffffff", 50);

	AllScenes::NewGame();
	LevelOne* level1 = new LevelOne("LevelOne");

	n2dGameAddScene(level1);
	n2dGameConfigFirstScene(level1);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}