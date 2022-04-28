#pragma once

#include "physics/ai/PhySimpleFollower.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::physics;

	class Rocket :
		public PhySimpleFollower
	{

	private:

	public:

		Rocket(const std::string& player, Vec2 position, Positional* target, float moveDelay);

		void DestroySelf();

	};
}