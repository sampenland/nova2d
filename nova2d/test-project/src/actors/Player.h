#pragma once
#include "physics/PhySprite.h"

namespace testproject
{
	using namespace novazero::physics;

	class Player
		: public PhySprite
	{

	private:

	public:

		Player(Vec2 position, Vec2Int size, unsigned char layer);

	};
}