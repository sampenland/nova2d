#include "Pawn1Controller.h"
#include "../enemies/Pawn1.h"
#include "core/Game.h"
#include "../Player.h"
#include "../scenes/Lvl1.h"

namespace spaceshooter
{
	using namespace novazero::core;

	Pawn1Controller::Pawn1Controller()
	{
		m_Pawn1Timer = new Timer(6000, true, std::bind(&Pawn1Controller::CreatePawn1, this));
	}

	void Pawn1Controller::CreatePawn1()
	{
		auto r = n2dRandomFloat(0, 10);

		int x = -16;
		if (r > 5)
		{
			x = Game::s_Width + 16;
		}

		int y = n2dRandomInt(Game::s_Height / 2, Game::s_Height);

		Pawn1* pawn1 = new Pawn1(Vec2(x, y));

		Player* player;
		if (Lvl1::s_Players == 1)
		{
			player = (Player*)n2dReferenceGet("player1");
		}
		else
		{
			if (n2dCoinFlip())
			{
				player = (Player*)n2dReferenceGet("player1");
			}
			else
			{
				player = (Player*)n2dReferenceGet("player2");

			}
		}

		Vec2 targetPosition = player->GetPosition();
		pawn1->AddPatrolPointWithFunction(targetPosition, std::bind(&Pawn1::LinearPatrolMove, pawn1));
		pawn1->EnableAI(true);
		pawn1->ConfigureOnPatrolComplete([=]() {

			pawn1->Shoot();
			pawn1->ClearPatrol();
			pawn1->ConfigureAliveBounds(Game::GetGameBounds(32));
			if (n2dCoinFlip())
			{
				pawn1->AddPatrolPointWithFunction(Vec2(Game::s_Width + 48, pawn1->GetY()), std::bind(&Pawn1::LinearPatrolMove, pawn1));
			}
			else
			{
				pawn1->AddPatrolPointWithFunction(Vec2(-48, pawn1->GetY()), std::bind(&Pawn1::LinearPatrolMove, pawn1));
			}

		});

		m_Pawn1s.push_back(pawn1);

	}

	void Pawn1Controller::DestroySelf()
	{
		m_Pawn1s.clear();
		m_Pawn1Timer->DestroySelf();
	}
}