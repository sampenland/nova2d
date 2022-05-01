#pragma once
#include "../graphics/Sprite.h"
#include "../physics/PhySensor.h"

namespace novazero
{
	namespace ai
	{
		using namespace graphics;
		using namespace physics;

		class SimpleDirectional
			: public Sprite
		{

		private:

			PhySensor* m_Sensor = nullptr;
			Vec2 m_TargetPos = Vec2(0, 0);
			Vec2 m_Direction = Vec2(0, 0);
			float m_Speed = 0.f;

		public:

			SimpleDirectional(Vec2 targetPos, float speed, float destroyTimeSeconds, const std::string& assetName, Vec2 position,
				Vec2Int size, unsigned char layer, const std::string& colliderName,
				const std::string& collisionGroup = "none");

			void Update();

			void DestroySelf();

		};
	}
}