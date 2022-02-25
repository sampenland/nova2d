#include "PawnController.h"

namespace spaceshooter
{
	PawnController::PawnController()
	{
		m_PawnShootMin = ValueManager::AddValue("pawn-shoot-min", 6000.f);
		m_PawnShootMax = ValueManager::AddValue("pawn-shoot-min", 12000.f);

		n2dDirectorAddToStackMinMax(false, 0, "PawnShoot", 
			70.f, 20.f, 5000.f, 20000.f, m_PawnShootMin, m_PawnShootMax);

	}

	void PawnController::CreateInstance(Vec2 position)
	{
		Pawn* pawn = new Pawn("pawn", position,
			Vec2Int(16, 16), 1, 0.0f, *m_PawnShootMin, *m_PawnShootMax);
		m_Pawns.push_back(pawn);
	}
}