#include "core/Game.h"
#include "scenes/AllScenes.h"
#include "scenes/MainMenu.h"
#include "scenes/level1/LevelOne.h"
#include "scenes/GameOver.h"

int main(int argc, char* argv[])
{
	using namespace thelastforest::scenes;
	using namespace novazero::core;

	// Game Config
	Game game("The Last Forest");
	//game.ConfigureDebugOverlay(true);
	n2dSetBackgroundColor("purple");

	n2dAddColor("highlight", "ffffff", 50);

	n2dAddColor("human-blue", "3da8eb", 50);
	n2dAddColor("human-yellow", "e8eb3d", 50);
	n2dAddColor("human-red", "eb3d3d", 50);

	//n2dLoadAndAddMusic("music", "res/audio/music.mp3");

	n2dLoadAndAddSoundEffect("start", "res/audio/novaStart.wav");
	n2dLoadAndAddSoundEffect("chop", "res/audio/chop.wav");
	n2dLoadAndAddSoundEffect("deadTree", "res/audio/deadTree.wav");
	n2dLoadAndAddSoundEffect("pickup", "res/audio/pickup.wav");
	n2dLoadAndAddSoundEffect("place", "res/audio/place.wav");
	n2dLoadAndAddSoundEffect("powerUp", "res/audio/powerUp.wav", 50);
	n2dLoadAndAddSoundEffect("humanDie", "res/audio/humanDie.wav");

	MainMenu* mainmenu = new MainMenu("MainMenu");
	LevelOne* level1 = new LevelOne("LevelOne");
	GameOver* gameover = new GameOver("GameOver");

	n2dGameAddScene(mainmenu);
	n2dGameAddScene(level1);
	n2dGameAddScene(gameover);

	n2dGameConfigFirstScene(mainmenu);

	game.Start();

	return Game::s_ExitCode;
}