#pragma once
#include "../graphics/Sprite.h"
#include "box2d/box2d.h"
#include "../maths/Rect.h"

namespace novazero
{
	namespace physics
	{
		using namespace graphics;
		using namespace maths;

		class PhySprite
			: public Sprite
		{

		private:

			b2Body* m_Body;

		public:

			PhySprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer,
				bool makeCopy = false);

			void ConfigurePhysicsRect(bool staticBody, Rect phyRect, float density = 0.f);
			void ConfigurePhysicsCircle(bool staticBody, Vec2 position, float radius, float density = 0.f);
		};
	}
}