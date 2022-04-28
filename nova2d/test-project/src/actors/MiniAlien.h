#pragma once
#include "physics/ai/PhySimpleFollower.h"
#include "core/Timer.h"
#include "particles/ParticleSystem.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::particles;

	class MiniAlien :
		public PhySimpleFollower
	{

	private:

		Timer* m_ReTargeter = nullptr;
		Timer* m_Shooter = nullptr;

		ParticleSystem* m_Jets = nullptr;

	public:

		MiniAlien(Positional* target, Vec2 position, float moveDelay);

		void ReTarget();
		void Shoot();

		void UpdateMiniAlien();

		void HitByRocket();

		void DestroySelf();

	};
}