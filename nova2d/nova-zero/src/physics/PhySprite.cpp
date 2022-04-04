#include "PhySprite.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace graphics;
		using namespace core;

		PhySprite::PhySprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer,
			bool makeCopy)
			: Sprite(assetName, position, size, layer, makeCopy)
		{

		}

		void PhySprite::ConfigurePhysicsRect(bool staticBody, Rect phyRect, float density)
		{
			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.position.Set(phyRect.x, phyRect.y);

			// Create body
			m_Body = world->CreateBody(&bodyDef);

			// Define the body collision shape
			b2PolygonShape shape;
			shape.SetAsBox(phyRect.w / 2, phyRect.h / 2);

			// Add the shape fixture to the body
			m_Body->CreateFixture(&shape, density);

		}

		void PhySprite::ConfigurePhysicsCircle(bool staticBody, Vec2 position, float radius, float density)
		{
			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.position.Set(position.x, position.y);

			// Create body
			m_Body = world->CreateBody(&bodyDef);

			// Define the body collision shape
			b2CircleShape shape;
			shape.m_radius = radius;

			// Add the shape fixture to the body
			m_Body->CreateFixture(&shape, density);
		}
	
	}
}