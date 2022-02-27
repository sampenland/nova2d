#pragma once
#include "core/NovaInstance.h"
#include "Pawn.h"
#include <vector>
#include "utils/ValueManager.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class PawnController : public NovaInstance
	{

	private:

		int m_CurrentWave = 0;

		std::vector<Pawn*> m_Pawns;

		int m_LeftPawns = 0;
		int m_RightPawns = 0;

		char m_Padding = 48;
		Vec2 m_Offset = Vec2(0.f, 100.f);
		int m_CreationHealth = 0;

		char m_CurrentRowL = 0;
		char m_CurrentRowR = 0;
		char m_MaxRows = 0;

		char m_CurrentColL = 0;
		char m_CurrentColR = 0;
		char m_MaxCols = 0;

		float* m_PawnShootMin = nullptr;
		float* m_PawnShootMax = nullptr;

		float* m_PawnMoveSpeed = nullptr;

	public:

		PawnController();

		void CreatePawn(int wave, int pawnCount);

		void Wave1(int pawnCount);

		int PawnCount() { return (int) m_Pawns.size(); }

		// Nova Instance overrides
		void CreateInstance(Vec2 position) override {};

	};
}