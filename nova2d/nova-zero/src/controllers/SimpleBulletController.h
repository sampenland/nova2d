#pragma once

#include "../maths/Rect.h"
#include "../core/Game.h"
#include "../core/BoundUser.h"
#include "../physics/Collider.h"

namespace novazero
{
	namespace controllers
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;
		using namespace physics;

		class SimpleBulletController
			: public EventListener, 
			public BoundUser,
			public Collider
		{

		private:

			Sprite* m_Sprite = nullptr;

			Vec2Int m_Start;
			Vec2Int m_End;

			Rect m_AliveBounds;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;

			int m_MoveSpeed = 0;

		public:

			SimpleBulletController(Vec2Int start, Vec2Int end, const float moveUpdateDelay);
			~SimpleBulletController();

			void AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			Sprite* GetSprite() const { return m_Sprite; }

			void Configure(int moveSpeed, Rect aliveBounds);
			void Update();
			bool OutOfBounds();

			void DestroySelf() override;
			void OnCollision(const Collision* collision) override;

		};
	}
}