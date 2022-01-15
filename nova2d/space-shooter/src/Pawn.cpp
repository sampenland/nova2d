#include "Pawn.h"

namespace spaceshooter
{
	using namespace novazero::graphics;

	Pawn::Pawn(std::string assetName, Vec2Int position, Vec2Int size, char layer, Positional* target, const float moveUpdateDelay)
		: SimpleFollower(target, moveUpdateDelay)
	{
		AddSprite(assetName, position, size, layer);
	}

	Pawn::~Pawn()
	{
		if (m_Sprite)
			delete m_Sprite;
	}
}