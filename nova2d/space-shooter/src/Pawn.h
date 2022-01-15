#pragma once

#include "ai/SimpleFollower.h"
#include <string>

namespace spaceshooter
{
	using namespace novazero::ai;

	class Pawn
		: public SimpleFollower
	{

	private:

	public:

		Pawn(std::string assetName, Vec2Int position, Vec2Int size, 
			char layer, Positional* target, const float moveUpdateDelay);
		
		Rect GetAliveBounds() const { return m_AliveBounds; }

		~Pawn();

	};
}