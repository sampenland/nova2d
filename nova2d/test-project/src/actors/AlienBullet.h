#pragma once
#include "physics/ai/PhySimpleFollower.h"
#include "core/Positional.h"
#include "physics/PhyContactListener.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	class AlienBullet :
		public PhySimpleFollower
	{

	private:

		PhyCollision* m_Collision = nullptr;

	public:

		AlienBullet(Vec2 position, Positional* target, float moveDelay);

		void HitPlayer(PhyBase* self, PhyBase* other);

		void DestroySelf();

	};
}