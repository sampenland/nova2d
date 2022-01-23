#pragma once
#include "../core/Game.h"

#include "../core/EventListener.h"
#include "../maths/Rect.h"
#include "../core/BoundUser.h"
#include "../physics/Collider.h"
#include "../core/Deleteable.h"

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
			public Collider,
			public Deleteable
		{

		private:

			Sprite* m_Sprite = nullptr;

			Vec2Int m_Start;
			Vec2Int m_End;

			float m_UpdateDirectionDelay = 0.0f;
			float m_DelayTime = 0;

			int m_MoveSpeed = 0;

			std::function<void()> f_OnDestroy = nullptr;

		public:

			SimpleBulletController(Vec2Int start, Vec2Int end, const float moveUpdateDelay);
			~SimpleBulletController();

			void AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			Sprite* GetSprite() const { return m_Sprite; }

			void Configure(int moveSpeed, Rect aliveBounds);
			void ConfigureDestroy(std::function<void()> f) { f_OnDestroy = f; }
			void Update();

			void DestroySelf() override;
			void OnCollision(Collision* collision) override;

		};
	}
}