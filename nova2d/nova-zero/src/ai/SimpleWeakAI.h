#pragma once
#include <functional>
#include <vector>
#include "../maths/Vec2Int.h"
#include "../graphics/Sprite.h"
#include "../core/Game.h"
#include "../core/BoundUser.h"
#include "../core/Deleteable.h"
#include "../core/Positional.h"

namespace novazero
{
	namespace ai
	{
		using namespace maths;
		using namespace graphics;
		using namespace core;
		using namespace physics;

		struct PatrolVec2IntWithMoveFunction
		{
			Vec2 patrolVec2;
			std::function<void()> moveFunction;
		};

		class SimpleWeakAI : 
			public BoundUser,
			public Deleteable,
			public Positional
		{

		private:

			std::vector<std::function<void()>> m_MoveFunctions;

			bool m_LoopMoving = true;
			int m_PatrolIndex = 0;

			int m_LoopStartIndex = 0;
			std::function<void()> f_OnPatrolComplete = nullptr;
			float m_DelayMS = 1000;
			float m_DelayMaxMS = 100;

			Vec2 m_MemoryMovement;
			bool m_ContinueAfterPatrolComplete = false;
			
			std::vector<Vec2*> m_PatrolPoints;

			bool m_UsingPatrolSpeedOverride = false;
			float* m_PatrolSpeedRef = nullptr;
			bool m_LookAtNextPosition = false;
			float m_ExtraAngle = 0.f;

		public:

			SimpleWeakAI();

			void Configure(int patrolDelayMS, bool loop = false) 
			{ 
				m_DelayMaxMS = (float)(patrolDelayMS / 1000);
				m_DelayMS = m_DelayMaxMS;

				m_LoopMoving = true;
				m_UsingPatrolSpeedOverride = false;
			}

			void Configure(float* patrolDelayMS, bool loop)
			{
				m_PatrolSpeedRef = patrolDelayMS;
				m_LoopMoving = loop;
				m_UsingPatrolSpeedOverride = true;
			}

			void ConfigureRotation(bool lookatNextPosition, float extraRotation)
			{
				m_LookAtNextPosition = lookatNextPosition;
				m_ExtraAngle = extraRotation;
			}

			void LookAt(Vec2Int target, int extraRotation)
			{
				float lookAtAngle = Vec2Int::LookAtAngle(Vec2Int((int)GetX(), (int)GetY()), 
					target, extraRotation);
				GetSprite()->SetAngle(lookAtAngle);
			}

			int GetWidth() { return GetSprite()->GetWidth(); }
			int GetHeight() { return GetSprite()->GetHeight(); }

			void ConfigureContinueAfterPatrolComplete(bool continueAfter) { m_ContinueAfterPatrolComplete = continueAfter; }
			void ConfigureOnPatrolComplete(std::function<void()> f) { f_OnPatrolComplete = f; }
			void ConfigureLoopIndex(int idx) { m_LoopStartIndex = idx; }
			void RestartPatrol() { m_PatrolIndex = 0; }
			void EnableAI(bool isEnabled);
			void ResetAI();

			void SetAllPatrolPoints(std::vector<Vec2*> points);
			std::vector<Vec2*> GetPatrolPoints()
			{
				return m_PatrolPoints;
			}
			Sprite* GetSprite()
			{
				return Positional::GetSprite();
			}

			inline void SetVisible(bool isVisible) 
			{ 
				Positional::GetSprite()->SetVisible(isVisible);
			}

			void AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, 
				unsigned char layer, bool makeCopy = false);

			void AddPatrolPointWithFunction(Vec2* point, std::function<void()> func);
			void AddPatrolPointWithFunction(Vec2 point, std::function<void()> func);
			void AddPatrolPointLinearMovement(Vec2 point);

			void RemovePatrolPointWithFunction(Vec2* point);

			void SetAllPatrol(std::vector<Vec2*> points, std::vector<std::function<void()>> funcs);
			void ClearPatrol();

			void Update();

			void DestroySelf();

		private:

			void LinearPatrolMove();
			std::function<void()> GetLinearPatrolMove() { return std::bind(&SimpleWeakAI::LinearPatrolMove, this); }
			

		};
	}
}