#include "PawnController.h"

namespace spaceshooter
{

	short PawnController::s_KilledPawnsThisWave = 0;
	unsigned int PawnController::s_KilledPawns = 0;

	PawnController::PawnController()
	{
		m_PawnShootMin = ValueManager::AddValue("pawn-shoot-min", 6000.f);
		m_PawnShootMax = ValueManager::AddValue("pawn-shoot-min", 12000.f);

		n2dDirectorAddToStackMinMax(false, 0, "PawnShoot", 
			70.f, 20.f, 5000.f, 20000.f, m_PawnShootMin, m_PawnShootMax);

		m_PawnMoveSpeed = ValueManager::AddValue("pawn-speed", 4.f);
		n2dDirectorAddToStack(true, 0, "PawnSpeed", 70.f, 0.050f, 5.5f, m_PawnMoveSpeed);

		m_CleanID = n2dAddUpdater(PawnController::Update, this);

	}

	void PawnController::Update()
	{
		std::vector<Pawn*>::iterator it = m_Pawns.begin();
		while (it != m_Pawns.end())
		{

			if ((*it)->m_Dead)
			{
				(*it)->DestroySelf();
				it = m_Pawns.erase(it);
				continue;
			}

			it++;
		}
	}

	void PawnController::CreatePawn(int wave, int pawnCount)
	{
		if (wave != m_CurrentWave)
		{
			s_KilledPawnsThisWave = 0;

			switch (wave)
			{
			case 1:
				m_Offset = Vec2(0.f, 54.f);
				m_Padding = 64;
				m_MaxRows = 2;
				m_MaxCols = 3;
				m_CurrentColL = m_MaxCols;
				m_CurrentColR = 0;
				m_CurrentRowL = m_CurrentRowR = 0;
				m_CreationHealth = 2;
				break;
			}

		}

		m_CurrentWave = wave;

		switch (wave)
		{
		case 1:
			Wave1(pawnCount);
			break;
		case 2:
			Wave2(pawnCount);
			break;
		}
	}

	void PawnController::Wave1(int pawnCount)
	{
		if (m_CurrentColL == -1 && m_CurrentRowL == -1 && 
			m_CurrentColR == -1 && m_CurrentRowR == -1) return;

		Vec2 position = Vec2(Game::s_Width / 2, -32);
		int inverter = 1;
		if (pawnCount % 2 == 0)
		{
			inverter = -1;
			position.x -= m_Padding;
		}
		else
		{
			inverter = 1;
			position.x += m_Padding;
		}

		Pawn* pawn = new Pawn("pawn", position,
			Vec2Int(16, 16), 1, m_PawnMoveSpeed, *m_PawnShootMin, *m_PawnShootMax, 4);
		pawn->Configure(m_PawnMoveSpeed, false);

		if (inverter == -1)
		{
			pawn->AddPatrolPointWithFunction(
				pawn->GetPosition().add(Vec2(0, m_Offset.y + m_MaxRows * m_Padding)),
				pawn->GetLinearPatrolMove());

			pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
				Vec2(inverter * m_CurrentColL * m_Padding, m_Offset.y + m_MaxRows * m_Padding)),
				pawn->GetLinearPatrolMove());

			pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
				Vec2(inverter * m_CurrentColL * m_Padding, m_Offset.y + (m_CurrentRowL + 1) * m_Padding)),
				pawn->GetLinearPatrolMove());

			if (m_CurrentRowL + 1 < m_MaxRows)
			{
				m_CurrentRowL++;
			}
			else
			{
				if (m_CurrentColL > 0)
				{
					m_CurrentColL--;
					m_CurrentRowL = 0;
				}
				else
				{
					m_CurrentColL = -1;
					m_CurrentRowL = -1;
				}
			}
		}
		else
		{
			pawn->AddPatrolPointWithFunction(
				pawn->GetPosition().add(Vec2(0, m_Offset.y + m_MaxRows * m_Padding)),
				pawn->GetLinearPatrolMove());

			pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
				Vec2(inverter * (m_MaxCols - m_CurrentColR) * m_Padding, m_Offset.y + m_MaxRows * m_Padding)),
				pawn->GetLinearPatrolMove());

			pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
				Vec2(inverter * (m_MaxCols - m_CurrentColR) * m_Padding, m_Offset.y + (m_CurrentRowR + 1) * m_Padding)),
				pawn->GetLinearPatrolMove());

			if (m_CurrentRowR + 1 < m_MaxRows)
			{
				m_CurrentRowR++;
			}
			else
			{
				if (m_CurrentColR < m_MaxCols)
				{
					m_CurrentColR++;
					m_CurrentRowR = 0;
				}
				else
				{
					m_CurrentColR = -1;
					m_CurrentRowR = -1;
				}
			}
		}

		m_Pawns.push_back(pawn);
	}

	void PawnController::Wave2(int pawnCount)
	{
		LOG(LVL_I, tostring(pawnCount));
	}

	void PawnController::DestroySelf()
	{
		n2dRemoveUpdater(m_CleanID);
	}
}