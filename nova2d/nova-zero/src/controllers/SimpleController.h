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

			SimpleController(const std::string& assetName, Vec2 position, Vec2Int size, char layer);
			~SimpleController();

			void SetMoveSpeed(float mSpeed);
			void MovementIsZeroX();
			void MovementIsZeroY();

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

		private:

			bool m_UsingAcceleration = false;

		protected:

			void SetAcceleration(AccelerationTypes type, float accelerationTimeMS, float deaccelerationTimeMS);
			bool IsUsingAcceleration() { return m_UsingAcceleration; }

		public:

			unsigned int m_AccelerationTweenX = 0;
			unsigned int m_AccelerationTweenY = 0;
			float m_MoveSpeed = 0.0f;
			
			bool m_StoppingX = true;
			bool m_StoppingY = true;
			bool m_StartingX = false;
			bool m_StartingY = false;

			float m_CurrentAccelerationX = 0.0f;
			float m_CurrentAccelerationY = 0.0f;

			AccelerationTypes m_AccelerationType = AccelerationTypes::Linear;
			float m_TotalAccelerationSpeedMS = 1000.f;
			float m_TotalDeaccelerationSpeedMS = 1000.f;

			Vec2 m_Velocity = Vec2(0, 0);
			Vec2Int m_Moving = Vec2Int(0, 0);

			void EnableAcceleration(bool v) { m_UsingAcceleration = v; }

		};
	}
}