#pragma once
#include "../graphics/Sprite.h"
#include "../core/TypeDefs.h"
#include <string>

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
			std::string m_ColliderName = "";

			void ConfigureCollider(Sprite* sprite, int collisionLayer, std::string colliderName);
			virtual void OnCollision(const Collision* collision) = 0;

		};
	}
}