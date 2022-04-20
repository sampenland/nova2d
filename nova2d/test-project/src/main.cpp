#include "core/Game.h"
#include "scenes/Play.h"
#include "scenes/GameOver.h"

int main(int argc, char* argv[])
{
	using namespace testproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("Test Project");
	game.SetDebugVerbose(true);

	Play* play = new Play("Play");
	GameOver* gameover = new GameOver("GameOver");

	n2dAddColor("space-black", "2e2e2e", 255);
	n2dSetBackgroundColor("space-black");

	n2dGameAddScene(play);
	n2dGameAddScene(gameover);
	n2dGameConfigFirstScene(play);

	game.Start();

	return Game::s_ExitCode;
}