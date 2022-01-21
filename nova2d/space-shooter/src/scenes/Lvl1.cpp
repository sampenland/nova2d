#include "Lvl1.h"
#include "../Player.h"
#include "../enemies/Leader.h"
#include "maths/Vec2Int.h"

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

		AddObjectToCleanUp(player);
		AddObjectToCleanUp(leader);

	}

	void Lvl1::Update()
	{

	}

	void Lvl1::End()
	{
		CleanUp();
	}

}