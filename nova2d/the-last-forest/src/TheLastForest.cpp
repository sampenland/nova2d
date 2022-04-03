#include "core/Game.h"
#include "scenes/AllScenes.h"
#include "scenes/MainMenu.h"
#include "scenes/level1/LevelOne.h"

int main(int argc, char* argv[])
{
	using namespace thelastforest::scenes;
	using namespace novazero::core;

	// Game Config
	Game game("The Last Forest");
	game.ConfigureDebugOverlay(true);
	n2dSetBackgroundColor("purple");

	n2dAddColor("highlight", "ffffff", 50);

	n2dAddColor("human-blue", "3da8eb", 50);
	n2dAddColor("human-yellow", "e8eb3d", 50);
	n2dAddColor("human-red", "eb3d3d", 50);

	n2dAssetsLoadAndAddTexture("grass", "res/grassTile.png");
	n2dAssetsLoadAndAddTexture("trees", "res/treesTile.png");
	n2dAssetsLoadAndAddTexture("tree", "res/treeTile.png");
	n2dAssetsLoadAndAddTexture("sun", "res/sun.png");
	n2dAssetsLoadAndAddTexture("player", "res/player.png");
	n2dAssetsLoadAndAddTexture("human", "res/human.png");
	n2dAssetsLoadAndAddTexture("water", "res/water.png");
	n2dAssetsLoadAndAddTexture("highlight", "res/highlightTile.png");
	n2dAssetsLoadAndAddTexture("deadtrees", "res/deadTrees.png");

	MainMenu* mainmenu = new MainMenu("MainMenu");
	LevelOne* level1 = new LevelOne("LevelOne");

	n2dGameAddScene(mainmenu);
	n2dGameAddScene(level1);

	n2dGameConfigFirstScene(mainmenu);

	while (Game::IsRunning())
	{
		game.Tick();
	}

	return Game::s_ExitCode;
}