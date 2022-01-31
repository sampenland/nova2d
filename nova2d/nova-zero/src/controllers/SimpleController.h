#pragma once
#include "../graphics/Sprite.h"
#include "../core/EventListener.h"
#include "../maths/Vec2Int.h"
#include "../utils/TextureLoader.h"
#include "../core/Game.h"
#include "../physics/TimeEffected.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		class SimpleController :
			public EventListener,
			public TimeEffected
		{

		private:

		protected:
			Sprite* m_Sprite = nullptr;

		public:

			SimpleController(std::string assetName, Vec2 position, Vec2Int size, char layer);
			~SimpleController();

			void SetMoveSpeed(float mSpeed);
			
			void SetPositionInt(int x, int y);
			void SetPosition(float x, float y);
			void SetX(float y);
			void SetY(float y);
			float GetX() const { return m_Sprite->GetX(); }
			float GetY() const { return m_Sprite->GetY(); }

			int GetWidth() const { return m_Sprite->GetWidth(); }
			int GetHeight() const { return m_Sprite->GetHeight(); }
			
			inline float GetMoveSpeed() const { return m_MoveSpeed; }
			inline Vec2Int GetPositionInt() const { return Vec2Int((int)m_Sprite->GetX(), (int)m_Sprite->GetY()); }
			inline Vec2 GetPosition() const { return Vec2(m_Sprite->GetX(), m_Sprite->GetY()); }

			void DestroySelf();

		public:

			float m_MoveSpeed = 0;
		};
	}
}