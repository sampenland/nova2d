#include "core/Game.h"
#include "scenes/SampleScene.h"

int main(int argc, char* argv[])
{
	using namespace emptyproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("nova2d Project");

	SampleScene scene = SampleScene("sampleScene");

	n2dSetBackgroundColor("purple");

	n2dGameAddScene(&scene);
	n2dGameConfigFirstScene(&scene);
	
	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}