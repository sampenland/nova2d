#pragma once

#include "../maths/Vec2.h"
#include "../maths/Rect.h"
#include "../core/Game.h"
#include "../core/Removeable.h"

namespace novazero
{
	namespace controllers
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		class SimpleBulletController
			: public core::EventListener,
			public core::Removeable
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
			void Configure(int moveSpeed, Rect aliveBounds);
			void Update();
			bool OutOfBounds();

			bool CheckAlive() override;
			void DestroySelf() override;

		};
	}
}