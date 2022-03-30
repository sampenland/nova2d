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

	n2dAddColor("blue", "0098db", 255);
	n2dSetBackgroundColor("blue");

	n2dGameAddScene(scene);
	n2dGameConfigFirstScene(scene);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}