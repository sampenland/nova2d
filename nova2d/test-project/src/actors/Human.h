#pragma once
#include "physics/ai/PhySimpleWeakAI.h"
#include "core/Timer.h"
#include "particles/ParticleSystem.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;
	using namespace novazero::particles;

	class Human :
		public PhySimpleWeakAI
	{
	private:

		Timer* m_MoveTimer = nullptr;
		int m_Skill = 8;

		ParticleSystem* m_Jets = nullptr;

	public:

		Human(Vec2 position, int skill = 8);

		void Move();
		void AtPlanet();
		void HumanUpdate();

		void DestroySelf();
	};
}