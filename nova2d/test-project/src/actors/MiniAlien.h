#pragma once
#include "physics/ai/PhySimpleFollower.h"
#include "core/Timer.h"

namespace testproject
{
	using namespace novazero::physics::ai;

	class MiniAlien :
		public PhySimpleFollower
	{

	private:

		Timer* m_ReTargeter = nullptr;
		Timer* m_Shooter = nullptr;

	public:

		MiniAlien(Positional* target, Vec2 position, float moveDelay);

		void ReTarget();
		void Shoot();

		void DestroySelf();

	};
}