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
				GetSprite()->SetPosition(Vec2(bodyPos.x - GetWidth() / 2, bodyPos.y - GetHeight() / 2));
				GetSprite()->SetAngle(n2dRadToDeg(m_Body->GetAngle()));
			}
		}

		void PhySprite::ConfigurePhysicsPolygon(bool staticBody, std::vector<Vec2> shapeVertices, const int vertexCount, float density, float friction)
		{
			if (vertexCount < 3)
			{
				LOG(LVL_NFE, "Polygon shape body not created. Too few points of shape.");
				return;
			}

			if (vertexCount > 8)
			{
				LOG(LVL_NFE, "Polygon shape body not created. Too many points of shape (change max points).");
				return;
			}

			if (vertexCount != (int)shapeVertices.size())
			{
				LOG(LVL_NFE, "Polygon shape body not created. Vertex count and number of vertices not equal.");
				return;
			}

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

			b2Vec2* vertices = new b2Vec2[shapeVertices.size()];

			if (!vertices)
			{
				LOG(LVL_NFE, "Could not free vertices for polygon shape.");
				return;
			}

			for (size_t i = 0; i < shapeVertices.size(); i++)
			{
				const b2Vec2 v = b2Vec2(shapeVertices[i].x * PHYSICS_SCALE, shapeVertices[i].y * PHYSICS_SCALE);
				vertices[i] = v;
			}

			b2PolygonShape shape;
			shape.Set(vertices, (int32)shapeVertices.size());

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);

			delete[] vertices;

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
			shape.SetAsBox(GetWidth() / 2 * PHYSICS_SCALE, GetHeight() / 2 * PHYSICS_SCALE);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);

		}

		void PhySprite::ConfigurePhysicsCircle(bool staticBody, float radius, float density, float friction)
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

			b2CircleShape shape;
			shape.m_radius = radius * PHYSICS_SCALE;

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
		}

		void PhySprite::ApplyForce(float force, Vec2 forcePosition)
		{
			if (m_Body)
			{
				const b2Vec2 f = b2Vec2((force * PHYSICS_MULTIPLIER), (force * PHYSICS_MULTIPLIER));
				if (forcePosition.x == 0 && forcePosition.y)
				{
					m_Body->ApplyForceToCenter(f, true);
				}
				else
				{
					const b2Vec2 pos = b2Vec2(m_Body->GetWorldCenter().x + forcePosition.x,
						m_Body->GetWorldCenter().y + forcePosition.y);

					b2Vec2 forceDirection = m_Body->GetWorldVector(b2Vec2(0, 1));

					m_Body->ApplyForce((force * PHYSICS_MULTIPLIER) * forceDirection, pos,  true);
				}
			}
		}

		void PhySprite::ApplyAngularForce(float force)
		{
			if (m_Body)
			{
				m_Body->ApplyAngularImpulse(force * (PHYSICS_MULTIPLIER / 30), true);
			}
		}

		void PhySprite::DestroySelf()
		{
			CleanUpdaters();

			Sprite::DestroySelf();
		}
	
	}
}