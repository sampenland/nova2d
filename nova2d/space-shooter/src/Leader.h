#pragma once
#include "ai/SimpleWeakAI.h"
#include "Pawn.h"

#include <vector>

namespace spaceshooter
{
	using namespace novazero::ai;

	class Leader
		: public SimpleWeakAI
	{
		
	private:

		std::vector<Pawn*> m_Pawns;

	public:

		Leader(std::string assetName, Vec2Int position, Vec2Int size, char layer);
		~Leader();

		void DestroySelf() override;

	};
}