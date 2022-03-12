#include "core/Game.h"
#include "scenes/SampleScene.h"

int main(int argc, char* argv[])
{
	using namespace emptyproject;
	using namespace novazero;
	using namespace core;

	// Game Config
	Game game("Empty Project");
	//game.ConfigureIcon("res/ship_01.png"); // Path to your icon (square)
	Game::SetGamePadding(32, 64, 32, 32);
	game.ConfigureDebugOverlay(true);
	game.s_InputHandler->ConfigureJoystickDeadzone(8000);

	// Background color
	n2dAddColor("novablue", "3f7178", 255);
	n2dSetBackgroundColor("novablue");

	// Textures
	SampleScene* sampleScene = new SampleScene("sampleScene");
	n2dGameAddScene(sampleScene);

	n2dGameConfigFirstScene(sampleScene);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}