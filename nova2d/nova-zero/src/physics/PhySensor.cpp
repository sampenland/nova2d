#include "PhySensor.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace novazero::core;

		PhySensor::PhySensor(std::string colliderName, bool staticBody,
			Vec2 position, Vec2 size, const std::string& collisionGroup, float density, float friction) 
			: PhyBase(colliderName, this, collisionGroup)
		{
			m_ID = n2dGameGetID();

			SetPosition(position);

			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.", __FILE__, __LINE__);
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData = reinterpret_cast<void*>((PhyBase*)this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;

			b2Vec2 pos = Vec2::PixelsToMeters(position);
			bodyDef.position.Set(pos.x, pos.y);

			m_Body = world->CreateBody(&bodyDef);

			b2PolygonShape shape;
			b2Vec2 boxSize = Vec2::PixelsToMeters(Vec2((float)size.x / 2.f, (float)size.y / 2.f));
			m_BodySize = boxSize;
			shape.SetAsBox(boxSize.x, boxSize.y);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.isSensor = true;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_Body->SetSleepingAllowed(false);

			m_Shape = Shapes::Circle;
			m_PhySize = size;
		}

		PhySensor::PhySensor(std::string colliderName, bool staticBody,
			Vec2 position, std::vector<Vec2> shapeVertices, const int vertexCount, const std::string& collisionGroup, float density, float friction)
			: PhyBase(colliderName, this, collisionGroup)
		{
			m_ID = n2dGameGetID();

			SetPosition(position);
			if (vertexCount < 3)
			{
				LOG(LVL_NFE, "Polygon shape body not created. Too few points of shape.", __FILE__, __LINE__);
				return;
			}

			if (vertexCount > 8)
			{
				LOG(LVL_NFE, "Polygon shape body not created. Too many points of shape (change max points).", __FILE__, __LINE__);
				return;
			}

			if (vertexCount != (int)shapeVertices.size())
			{
				LOG(LVL_NFE, "Polygon shape body not created. Vertex count and number of vertices not equal.", __FILE__, __LINE__);
				return;
			}

			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.", __FILE__, __LINE__);
				return;
			}

			if (!GetPhySprite())
			{
				LOG(LVL_NFE, "Tryinig to create a physics sprite with no sprite.", __FILE__, __LINE__);
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData = reinterpret_cast<void*>((PhyBase*)this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			
			b2Vec2 pos = Vec2::PixelsToMeters(position);
			bodyDef.position.Set(pos.x, pos.y);

			m_Body = world->CreateBody(&bodyDef);

			b2Vec2* vertices = new b2Vec2[shapeVertices.size()];

			if (!vertices)
			{
				LOG(LVL_NFE, "Could not free vertices for polygon shape.", __FILE__, __LINE__);
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
			fixtureDef.isSensor = true;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_Body->SetSleepingAllowed(false);

			delete[] vertices;
		}

		PhySensor::PhySensor(std::string colliderName, bool staticBody,
			Vec2 position, float radiusInPixels, const std::string& collisionGroup, float density, float friction)
			: PhyBase(colliderName, this, collisionGroup)
		{
			m_ID = n2dGameGetID();

			SetPosition(position);
			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.", __FILE__, __LINE__);
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData = reinterpret_cast<void*>((PhyBase*)this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			
			b2Vec2 pos = Vec2::PixelsToMeters(position);
			bodyDef.position.Set(pos.x, pos.y);

			m_Body = world->CreateBody(&bodyDef);

			b2CircleShape shape;
			shape.m_radius = n2dPixelsToMeters(radiusInPixels) * PHYSICS_SCALE;

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.isSensor = true;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_Body->SetSleepingAllowed(false);

			m_Shape = Shapes::Circle;
			m_Radius = radiusInPixels;
		}

		unsigned int PhySensor::GetPhyID() const
		{
			return m_ID;
		}

		void PhySensor::DestroySelf()
		{
			if (m_Body)
				Game::s_SceneManager->s_PhyCleaners.push_back(m_Body);
		}
	}
}