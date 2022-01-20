#include "GamePlay.h"
#include "../Player.h"
#include "../Leader.h"
#include "maths/Vec2Int.h"

namespace spaceshooter
{
	GamePlay::GamePlay()
	{
		
	}

	GamePlay::~GamePlay()
	{

	}

	void GamePlay::Start()
	{
		Player* player = new Player("player", Vec2Int((int)Game::s_Width / 2 - 8, (int)Game::s_Height - 64), Vec2Int(16, 16), 1);
		player->Configure(3000);
		player->ConfigureMove(3);
		player->SetMoveBounds(Game::GetGameBounds());

		Game::s_ReferenceManager->AddReference("player", player);

		Leader enemy("leader", Vec2Int((int)Game::s_Width / 2 - 8, -48), Vec2Int(16, 16), 1);
		enemy.ConfigureAliveBounds(Game::GetGameBounds());
	}

	void GamePlay::End()
	{

	}

	void GamePlay::Update()
	{

	}
}