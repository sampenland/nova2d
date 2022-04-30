#include "core/Game.h"
#include "scenes/Play.h"

int main(int argc, char* argv[])
{
	using namespace withinsafety;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("nova2d Project");

	Play* play = new Play("sampleScene");

	n2dSetBackgroundColor("purple");

	n2dGameAddScene(play);
	n2dGameConfigFirstScene(play);

	game.Start();

	return Game::s_ExitCode;
}