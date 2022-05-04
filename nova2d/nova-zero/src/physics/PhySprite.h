#pragma once
#include "../graphics/Sprite.h"
#include "Box2D/Box2D.h"
#include "../maths/Rect.h"
#include "../physics/PhyBase.h"

namespace novazero
{
	namespace physics
	{
		using namespace graphics;
		using namespace maths;

		class PhySprite : 
			public PhyBase,
			public Sprite
		{

		private:		

			bool m_RectShape = false;
			bool m_CircleShape = false;

			b2Body* m_Body = nullptr;
			bool m_AutoRotate = true;

			Vec2 m_PhySize = Vec2(0, 0);
			float m_Radius = 1.f;

			b2FixtureDef fixtureDef;
			float m_Density = 1.f;
			float m_Friction = 1.f;
			bool m_IsSensor = 1.f;
			float m_Restitution = 1.f;
			float m_RestitutionThres = 1.f;


		public:

			PhySprite(const std::string& assetName, Vec2 position, 
				Vec2 size, unsigned char layer, Vec2Int displaySize, 
				std::string colliderName, const std::string& collisionGroup = "none");

			unsigned int GetPhyID() const override;

			b2Body* GetBody() const 
			{
				return m_Body;
			}

			void ConfigurePhysicsRect(bool staticBody, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsPolygon(bool staticBody, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsCircle(bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsSensorCircle(bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);

			void EnableRotation(bool val);
			
			void DisableAutoRotation()
			{
				m_AutoRotate = false;
			}

			void EnableAutoRotation()
			{
				m_AutoRotate = true;
			}

			/*
			Force position 0,0 is center of mass
			*/
			void ApplyForce(float force, Directions direction);
			void ApplyForce(Vec2 forceDirNormalized, float magnitude);
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