#include "Pawn1Controller.h"
#include "../enemies/Pawn1.h"
#include "core/Game.h"
#include "../Player.h"
#include "../scenes/Lvl1.h"
#include "utils/ValueManager.h"

namespace spaceshooter
{
	using namespace novazero::core;

	Pawn1Controller::Pawn1Controller()
	{
		return;
		// LINK TO DIRECTOR ---------------------------------
		float* min = n2dValueManagerAdd("pawn1-creation-min", 6000.f);
		float* max = n2dValueManagerAdd("pawn1-creation-max", 12000.f);
		n2dDirectorAddToStackMinMax(true, 0, "Pawn1 Creation", 70.f, 50.f, 1000.f, 20000.f, min, max);
		// ---------------------------------------------------
		m_Pawn1Timer = new Timer(min, max, std::bind(&Pawn1Controller::CreatePawn1, this));
	}

	void Pawn1Controller::CreatePawn1()
	{
		int x = -16;
		if (n2dCoinFlip())
		{
			x = Game::s_Width + 16;
		}

		int y = n2dRandomInt(Game::s_Height / 2, Game::s_Height);

		Pawn1* pawn1 = new Pawn1(Vec2((float)x, (float)y));

		Player* player = (Player*)n2dReferenceGet("player");
		
		Vec2 targetPosition = player->GetPosition();
		pawn1->AddPatrolPointWithFunction(targetPosition, std::bind(&Pawn1::LinearPatrolMove, pawn1));
		pawn1->EnableAI(true);
		pawn1->ConfigureOnPatrolComplete([=]() {

			pawn1->Shoot();
			pawn1->ClearPatrol();
			pawn1->ConfigureAliveBounds(Game::GetGameBounds(32));
			if (n2dCoinFlip())
			{
				pawn1->AddPatrolPointWithFunction(Vec2((float)Game::s_Width + 48.f, pawn1->GetY()), std::bind(&Pawn1::LinearPatrolMove, pawn1));
			}
			else
			{
				pawn1->AddPatrolPointWithFunction(Vec2(-48.f, pawn1->GetY()), std::bind(&Pawn1::LinearPatrolMove, pawn1));
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