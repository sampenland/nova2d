#include "core/Game.h"
#include "scenes/DemoScene.h"

int main(int argc, char* argv[])
{
	using namespace testproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("Test Project");

	DemoScene* scene = new DemoScene("demoScene");

	n2dSetBackgroundColor("purple");

	n2dGameAddScene(scene);
	n2dGameConfigFirstScene(scene);

	game.Start();

	return Game::s_ExitCode;
}