#pragma once
#include "ai/SimpleWeakAI.h"
#include "core/Timer.h"
#include "../Enums.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::core;
		using namespace novazero::ai;
		using namespace novazero::physics;

		class Human : 
			public SimpleWeakAI
		{

		private:

			Timer* m_ThinkTimer = nullptr;
			float m_ThinkSpeed = 1000.f;
			bool m_Waiting = false;

			bool m_HandlingCollision = false;

			bool m_StepDown = true;
			const unsigned int m_Step = 88;

			unsigned int m_AttackStrength = 1;
			unsigned int m_MaxAttacks = 1;
			unsigned int m_Attacks = 1;

			unsigned int m_Column = 0;

		public:

			Human(Vec2 position, unsigned int column, Vec2Int size, unsigned char layer);

			void ThinkNextMove();

			void OnCollision(Collision* collision);

			void HandleStepTo(unsigned int gridPos, GridTypes type);

			void PowerUp();
			void Die();

			void DestroySelf();
 
		};
	}
}