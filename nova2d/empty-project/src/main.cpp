#include "core/Game.h"
#include "scenes/TimelinesExample.h"

int main(int argc, char* argv[])
{
	using namespace emptyproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("Empty Project");

	TimelinesExample* scene = new TimelinesExample("scene");

	n2dGameAddScene(scene);
	n2dGameConfigFirstScene(scene);
	
	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}