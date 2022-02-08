#pragma once
#include "../graphics/Sprite.h"
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
			unsigned int m_ID;

			int m_CollisionLayer = 0;
			std::string m_ColliderName = "";
			bool m_UsingCollider = false;

			std::function<void(Collision* c)> f_OnCollision = nullptr;

			void ConfigureCollider(Sprite* sprite, int collisionLayer, const std::string& colliderName);
			void ConfigureOnCollision(std::function<void(Collision*)> onCollision) { f_OnCollision = onCollision; }
			virtual void OnCollision(Collision* collision) = 0;

		};
	}
}