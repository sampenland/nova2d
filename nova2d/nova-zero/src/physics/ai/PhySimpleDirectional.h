#pragma once
#include "../../maths/Maths.h"
#include "../PhySprite.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace maths;
			using namespace physics;

			class PhySimpleDirectional :
				public PhySprite
			{

			private:

				Vec2 m_Direction = Vec2(0.f, 0.f);
				float m_Speed = 0.f;
				float m_DestroyTime = 0.f;

			public:

				PhySimpleDirectional(Vec2 direction, float speed, float autoDestroySeconds,
					const std::string& assetName, Vec2 position, Vec2 size,
					unsigned char layer, Vec2Int displaySize, std::string colliderName,
					const std::string& collisionGroup = "none");

				void Update();

				void DestroySelf();
			
			};
		}
	}
}