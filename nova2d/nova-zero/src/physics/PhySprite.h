#pragma once
#include "../graphics/Sprite.h"
#include "box2d/box2d.h"
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

		public:

			PhySprite(const std::string& assetName, Vec2 position, 
				Vec2 size, unsigned char layer, Vec2Int displaySize, 
				std::string colliderName);

			b2Body* GetBody() const 
			{
				return m_Body;
			}
			void ConfigurePhysicsRect(bool staticBody, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsPolygon(bool staticBody, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsCircle(bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);
			void ConfigurePhysicsSensorCircle(bool staticBody, float radius, float density = 0.5f, float friction = 0.3f);

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