#pragma once
#include "../graphics/Sprite.h"
#include "../core/TypeDefs.h"


namespace novazero
{
	namespace physics
	{
		using namespace graphics;

		class Collision;
		
		class Collider
		{

		private:
			

		protected:


		public:

			Collider(int collisionLayer);
			~Collider();

			Sprite* m_ColliderSprite;

			int m_CollisionLayer = 0;
			unsigned int m_ID;

			void ConfigureCollider(Sprite* sprite, int collisionLayer);
			virtual void OnCollision(const Collision* collision) = 0;

		};
	}
}