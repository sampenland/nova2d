#pragma once
#include <functional>
#include <vector>
#include "../maths/Vec2Int.h"
#include "../logging/logging.h"
#include "../graphics/Sprite.h"
#include "../core/Game.h"
#include "../core/BoundUser.h"
#include "../physics/Collider.h"

typedef std::function<void()> f_MovePtrFunction;

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
			Vec2Int patrolVec2Int;
			f_MovePtrFunction moveFunction;
		};

		class SimpleWeakAI
			: public BoundUser, public Collider
		{

		private:

			std::vector<f_MovePtrFunction> m_MoveFunctions;

			bool m_LoopMoving = true;
			int m_PatrolIndex = -1;

			int m_LoopStartIndex = 0;
			std::function<void()> f_OnPatrolComplete = nullptr;
			float m_Delay = 1000.f;
			float m_DelayMax = 1000.f;

		protected:
			
			std::vector<Vec2Int> m_PatrolPoints;
			Sprite* m_Sprite = nullptr;

		public:

			SimpleWeakAI();
			~SimpleWeakAI();

			void Configure(float patrolDelay, bool loop) { m_DelayMax = patrolDelay; m_LoopMoving = true; }
			void ConfigureOnPatrolComplete(std::function<void()> f) { f_OnPatrolComplete = f; }
			void ConfigureLoopIndex(int idx) { m_LoopStartIndex = idx; }
			void RestartPatrol() { m_PatrolIndex = 0; }
			void EnableAI(bool isEnabled);
			void ResetAI();

			inline int GetX() const { return m_Sprite->GetX(); }
			inline int GetY() const { return m_Sprite->GetY(); }
			inline void SetPosition(int x, int y) { m_Sprite->SetX(x); m_Sprite->SetY(y); }

			inline void SetVisible(bool isVisible) { m_Sprite->m_Visible = isVisible; }

			void AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);

			void AddPatrolPointWithFunction(Vec2Int point, f_MovePtrFunction func);
			void RemovePatrolPointWithFunction(Vec2Int point);

			void SetAllPatrol(std::vector<Vec2Int> points, std::vector<f_MovePtrFunction> funcs);

			void LinearPatrolMove();
			
			void Update();
			void OnCollision(Collision* collision) override { };

		};
	}
}