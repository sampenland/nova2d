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

			bool m_RectShape = false;
			bool m_CircleShape = false;

			Vec2Int m_Size = Vec2Int(0, 0);
			float m_Radius = 1.f;
			b2FixtureDef fixtureDef;
			float m_Density = 1.f;
			float m_Friction = 1.f;
			bool m_IsSensor = 1.f;
			float m_Restitution = 1.f;
			float m_RestitutionThres = 1.f;

		public:

			PhySprite(const std::string& assetName, Vec2 position, 
				Vec2Int size, unsigned char layer, Vec2Int displaySize);

			b2Body* GetBody() const 
			{
				return m_Body;
			}
			void ConfigurePhysicsRect(const std::string& colliderName, bool staticBody, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsPolygon(const std::string& colliderName, bool staticBody, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsCircle(const std::string& colliderName, bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsSensorCircle(const std::string& colliderName, bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);

			std::string GetColliderName() const;

			/*
			Force position 0,0 is center of mass
			*/
			void ApplyForce(float force, Directions direction);
			void ApplyAngularForce(float force);

			void Update();

			int GetWidth() const;
			int GetHeight() const;

			void SetPosition(Vec2 position);
			void SetScale(float factor);

			void DestroySelf();
		};
	}
}