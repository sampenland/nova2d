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

		char m_CurrentRow = 0;
		char m_MaxRows = 16;

		char m_CurrentCol = 0;
		char m_MaxCols = 6;

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