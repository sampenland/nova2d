#pragma once
#include "utils/timeline/TimelineInstance.h"
#include "Pawn.h"
#include <vector>
#include "utils/ValueManager.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::utils::timeline;

	class PawnController : public TimelineInstance
	{

	private:

		unsigned int m_CleanID = 0;
		int m_CurrentWave = 0;

		std::vector<Pawn*> m_Pawns;

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

		static short s_KilledPawnsThisWave;
		static unsigned int s_KilledPawns;

	public:

		PawnController();

		void CreatePawn(int wave, int pawnCount);

		void Update();
		void Wave1(int pawnCount);
		void Wave2(int pawnCount);

		int PawnCount() 
		{ 
			return (int)m_Pawns.size();
		}

		void DestroySelf();

	};
}