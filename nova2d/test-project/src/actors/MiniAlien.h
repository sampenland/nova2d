#pragma once
#include "physics/ai/PhySimpleFollower.h"

namespace testproject
{
	using namespace novazero::physics::ai;

	class MiniAlien :
		public PhySimpleFollower
	{

	private:

	public:

		MiniAlien(Vec2 position, Positional* target, float moveDelay);

		void DestroySelf();

	};
}