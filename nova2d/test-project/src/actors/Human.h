#pragma once
#include "physics/ai/PhySimpleWeakAI.h"
#include "core/Timer.h"

namespace testproject
{
	using namespace novazero::physics::ai;
	using namespace novazero::core;

	class Human :
		public PhySimpleWeakAI
	{
	private:

		Timer* m_MoveTimer = nullptr;

	public:

		Human(Vec2 position);

		void Move();
		void AtPlanet();

		void DestroySelf();
	};
}