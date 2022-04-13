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

			b2Body* m_Body = nullptr;
			std::string m_ColliderName = "phySprite";

		public:

			PhySprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer,
				bool makeCopy = false);

			void ConfigurePhysicsRect(const std::string& colliderName, bool staticBody, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsPolygon(const std::string& colliderName, bool staticBody, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsCircle(const std::string& colliderName, bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);

			std::string GetColliderName() const;

			/*
			Force position 0,0 is center of mass
			*/
			void ApplyForce(float force, Vec2 forcePosition= Vec2(0,0));
			void ApplyAngularForce(float force);

			void Update();

			void DestroySelf();
		};
	}
}