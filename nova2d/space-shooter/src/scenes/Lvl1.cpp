#include "Lvl1.h"
#include "../Player.h"
#include "../enemies/Leader.h"
#include "maths/Vec2Int.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	Lvl1::Lvl1(std::string sceneName) : Scene(sceneName)
	{
		
	}

	Lvl1::~Lvl1()
	{

	}

	void Lvl1::Start()
	{
		Player* player = new Player("player", Vec2Int((int)Game::s_Width / 2 - 8, (int)Game::s_Height - 64), Vec2Int(16, 16), 1);
		player->Configure(1500);
		player->ConfigureMove(3);
		player->SetMoveBounds(Game::GetGameBounds());

		n2dReferenceAdd("player", player);

		Leader* leader = new Leader("leader", Vec2Int((int)Game::s_Width / 2 - 8, -48), Vec2Int(16, 16), 1);
		leader->ConfigureAliveBounds(Game::GetGameBounds());

		const int scoreSize = 128;
		Text* score = new Text("font1", "Score: 0", "white", Rect(Game::s_Width - scoreSize - 8, 8, scoreSize, 16), 0);
		n2dAddDrawable(score, 0);
		n2dReferenceAdd("score", score);

		AddObjectToCleanUp(player);
		AddObjectToCleanUp(leader);
		AddObjectToCleanUp(score);

	}

	void Lvl1::Update()
	{

	}

	void Lvl1::End()
	{
		n2dReferenceRemove("score");
		CleanUp();
	}

}