#pragma once
#include "physics/ai/PhySimpleFollower.h"
#include "core/Positional.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	class AlienBullet :
		public PhySimpleFollower
	{

	private:

	public:

		AlienBullet(Vec2 position, Positional* target, float moveDelay);

		void DestroySelf();

	};
}