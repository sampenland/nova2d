#include "core/Game.h"
#include "scenes/EditorScene.h"

int main(int argc, char* argv[])
{
	using namespace particleeditor;
	using namespace novazero::core;

	// Game Config
	Game game("nova2d Particle Editor v.0.1 pre-alpha");

	EditorScene* editorScene = new EditorScene("editorScene");

	n2dAddColor("background", "2e2e2e", 255);
	n2dSetBackgroundColor("background");

	n2dGameAddScene(editorScene);
	n2dGameConfigFirstScene(editorScene);

	game.Start();

	return Game::s_ExitCode;
}