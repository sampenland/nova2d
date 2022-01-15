#pragma once

#include "../maths/Vec2.h"
#include "../maths/Rect.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		class SimpleBulletController
			: public core::EventListener
		{

		private:

			Sprite* m_Sprite = nullptr;

			Vec2 m_Start;
			Vec2 m_End;

			Rect m_AliveBounds;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;

			int m_MoveSpeed = 0;

		public:

			SimpleBulletController(Vec2 start, Vec2 end, const float moveUpdateDelay);
			~SimpleBulletController();

			void AddSprite(Vec2 position, const char* spriteSheet, Vec2 size, char layer);
			void Configure(int moveSpeed, Rect aliveBounds);
			void Update();
			bool OutOfBounds();

		};
	}
}