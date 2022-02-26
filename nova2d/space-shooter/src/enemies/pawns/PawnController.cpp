#include "PawnController.h"

namespace spaceshooter
{
	PawnController::PawnController()
	{
		m_PawnShootMin = ValueManager::AddValue("pawn-shoot-min", 6000.f);
		m_PawnShootMax = ValueManager::AddValue("pawn-shoot-min", 12000.f);

		n2dDirectorAddToStackMinMax(false, 0, "PawnShoot", 
			70.f, 20.f, 5000.f, 20000.f, m_PawnShootMin, m_PawnShootMax);

		m_PawnMoveSpeed = ValueManager::AddValue("pawn-speed", 0.5f);

		n2dDirectorAddToStack(true, 0, "PawnSpeed", 70.f, 10.f, 1.f, m_PawnMoveSpeed);

	}

	void PawnController::CreatePawn(int wave, int pawnCount)
	{
		if (wave != m_CurrentWave)
		{
			m_LeftPawns = 0;
			m_RightPawns = 0;
		}

		m_CurrentWave = wave;

		switch (wave)
		{
		case 1:
			Wave1(pawnCount);
			break;
		}
	}

	void PawnController::Wave1(int pawnCount)
	{
		if (m_CurrentCol == -1 || m_CurrentRow == -1) return;

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
			Vec2Int(16, 16), 1, m_PawnMoveSpeed, *m_PawnShootMin, *m_PawnShootMax);

		
		pawn->AddPatrolPointWithFunction(
			pawn->GetPosition().add(Vec2(0, m_MaxRows * m_Padding)),
			pawn->GetLinearPatrolMove());

		pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
			Vec2(inverter * (m_MaxCols - m_CurrentCol) * m_Padding, (m_MaxRows - m_CurrentRow) * m_Padding)),
			pawn->GetLinearPatrolMove());

		pawn->AddPatrolPointWithFunction(pawn->GetPosition().add(
			Vec2(inverter * (m_MaxCols - m_CurrentCol) * m_Padding, (m_MaxRows - m_CurrentRow) * m_Padding)),
			pawn->GetLinearPatrolMove());

		if (m_CurrentRow < m_MaxRows)
		{
			m_CurrentRow++;
		}
		else
		{
			if (m_CurrentCol < m_MaxCols)
			{
				m_CurrentCol++;
			}
			else
			{
				m_CurrentCol = -1;
				m_CurrentRow = -1;
			}
		}

		m_Pawns.push_back(pawn);
	}
}