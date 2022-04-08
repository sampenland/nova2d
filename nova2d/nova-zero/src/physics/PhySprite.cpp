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
			m_ID = n2dGameGetID();

			auto uID = n2dAddUpdater(PhySprite::Update, this);
			m_CleanUpdaters.push_back(uID);
		}

		void PhySprite::Update()
		{
			if (m_Body && GetSprite())
			{
				b2Vec2 bodyPos = m_Body->GetPosition();
				GetSprite()->SetPosition(Vec2(bodyPos.x, bodyPos.y));
				LOGS(m_Body->GetLinearVelocity().y);
			}
		}

		void PhySprite::ConfigurePhysicsRect(bool staticBody, float density, float friction)
		{
			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.");
				return;
			}

			if (!GetSprite())
			{
				LOG(LVL_NFE, "Tryinig to create a physics sprite with no sprite.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			bodyDef.position.Set(GetX(), GetY());

			m_Body = world->CreateBody(&bodyDef);

			b2PolygonShape shape;
			shape.SetAsBox(GetWidth() / 2, GetHeight() / 2);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);

		}

		void PhySprite::ConfigurePhysicsCircle(bool staticBody, float radius, float density)
		{
			//b2World* world = n2dCurrentPhyWorld();

			//if (!world)
			//{
			//	LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.");
			//	return;
			//}

			//if (m_Body)
			//	world->DestroyBody(m_Body);

			//b2BodyDef bodyDef;
			//bodyDef.position.Set(position.x, position.y);

			//// Create body
			//m_Body = world->CreateBody(&bodyDef);

			//// Define the body collision shape
			//b2CircleShape shape;
			//shape.m_radius = radius;

			//// Add the shape fixture to the body
			//m_Body->CreateFixture(&shape, density);
		}

		void PhySprite::ApplyForce(Vec2 force)
		{
			if (m_Body)
			{
				const b2Vec2 f = b2Vec2(force.x, force.y);
				m_Body->ApplyForce(f, m_Body->GetLocalCenter(), true);
			}
		}

		void PhySprite::DestroySelf()
		{
			CleanUpdaters();

			Sprite::DestroySelf();
		}
	
	}
}