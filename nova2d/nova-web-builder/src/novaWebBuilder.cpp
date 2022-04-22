#include "core/Game.h"
#include "scenes/MainScene.h"

int main(int argc, char* argv[])
{
	using namespace webbuilder;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("nova2d Web Builder");

	MainScene* mainScene = new MainScene("sampleScene");

	n2dSetBackgroundColor("blue");

	n2dGameAddScene(mainScene);
	n2dGameConfigFirstScene(mainScene);

	game.Start();

	return Game::s_ExitCode;
}