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
			
			unsigned int m_CleanID = 0;
			bool m_Enabled = true;

			Positional* m_AttachedPositional = nullptr;
			Vec2 m_Velocity = Vec2(0, 0);
			float m_Friction = 0.01f;

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
			void ConfigureCollider(Sprite* sprite, int collisionLayer, const std::string& colliderName, Positional* positional);
			void ConfigureOnCollision(std::function<void(Collision*)> onCollision) { f_OnCollision = onCollision; }
			
			void SetColliderEnabled(bool isEnabled) { m_Enabled = isEnabled; }
			bool IsColliderEnabled() const
			{
				return m_Enabled;
			}

			void ConfigurePhysicsPositional(Positional* positional);
			void Update();
			void HandleFriction();

			void SetFriction(float friction);
			float GetFriction() const { return m_Friction; }

			void SetVelocity(Vec2 vel);
			void AddVelocity(Vec2 vel);
			Vec2 GetVelocity() const { return m_Velocity; }
			
			virtual void OnCollision(Collision* collision) = 0;

		};
	}
}