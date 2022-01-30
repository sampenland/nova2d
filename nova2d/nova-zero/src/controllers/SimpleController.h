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

			SimpleController(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			~SimpleController();

			void SetMoveSpeed(float mSpeed);
			
			void SetPosition(int x, int y);
			void SetX(int y);
			void SetY(int y);
			int GetX() const { return m_Sprite->GetX(); }
			int GetY() const { return m_Sprite->GetY(); }

			int GetWidth() const { return m_Sprite->GetWidth(); }
			int GetHeight() const { return m_Sprite->GetHeight(); }
			
			inline float GetMoveSpeed() const { return m_MoveSpeed; }
			inline Vec2Int GetPosition() const { return Vec2Int(m_Sprite->GetX(), m_Sprite->GetY()); }

			void DestroySelf();

		public:

			float m_MoveSpeed = 0;
		};
	}
}