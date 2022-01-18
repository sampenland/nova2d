#pragma once
#include "../graphics/Sprite.h"
#include "../core/TypeDefs.h"

namespace novazero
{
	namespace physics
	{
		using namespace graphics;

		class Collider
		{

		private:

		protected:

			Collider(int collisionLayer);

		public:

			int m_CollisionLayer = 0;
			unsigned int m_ID;
			Sprite* m_Sprite;
			f_CollisionPassFunction f_OnCollision;

			void Configure(Sprite* sprite, f_CollisionPassFunction onCollision);

		};
	}
}