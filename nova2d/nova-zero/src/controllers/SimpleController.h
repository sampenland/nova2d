#pragma once
#include "../graphics/Sprite.h"
#include "../core/EventListener.h"
#include "../maths/Vec2.h"
#include "../utils/TextureLoader.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		class SimpleController :
			public EventListener
		{

		private:

			Sprite* m_Sprite = nullptr;

		public:

			SimpleController(const char* spriteSheet, Vec2 position, Vec2 size, char layer);
			~SimpleController();

			void SetMoveSpeed(int mSpeed);
			
			void SetPosition(int x, int y);
			void SetX(int y);
			void SetY(int y);

			int GetWidth() const { return m_Sprite->GetWidth(); }
			int GetHeight() const { return m_Sprite->GetHeight(); }
			
			inline int GetMoveSpeed() const { return m_MoveSpeed; }
			inline Vec2 GetPosition() const { return Vec2((float)m_Sprite->GetX(), (float)m_Sprite->GetY()); }

		public:

			int m_MoveSpeed = 0;
		};
	}
}