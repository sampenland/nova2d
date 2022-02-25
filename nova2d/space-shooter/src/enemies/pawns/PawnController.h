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

		std::vector<Pawn*> m_Pawns;

		float* m_PawnShootMin = nullptr;
		float* m_PawnShootMax = nullptr;

	public:

		PawnController();

		void CreateInstance(Vec2 position) override;

	};
}