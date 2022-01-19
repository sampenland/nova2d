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
			bool m_UsingCollider = false;

			std::function<void(Collision* c)> f_OnCollision = nullptr;

			void ConfigureCollider(Sprite* sprite, int collisionLayer, std::string colliderName);
			void ConfigureOnCollision(std::function<void(Collision*)> onCollision) { f_OnCollision = onCollision; }
			virtual void OnCollision(Collision* collision) = 0;

		};
	}
}