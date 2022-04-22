#include "core/Game.h"
#include "scenes/SampleScene.h"

int main(int argc, char* argv[])
{
	using namespace emptyproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("nova2d Project");

	SampleScene* scene = new SampleScene("sampleScene");

	n2dSetBackgroundColor("purple");

	n2dGameAddScene(scene);
	n2dGameConfigFirstScene(scene);
	
	game.Start();

	return Game::s_ExitCode;
}