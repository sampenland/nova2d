#include "PhySprite.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace graphics;
		using namespace core;

		PhySprite::PhySprite(const std::string& assetName, Vec2 position, Vec2 size, 
			unsigned char layer, Vec2Int displaySize, std::string colliderName)
			: Sprite(assetName, position, displaySize, layer), PhyBase(colliderName)
		{
			m_ID = n2dGameGetID();
			m_PhySize = size;

			auto uID = n2dAddUpdater(PhySprite::Update, this);
			m_CleanUpdaters.push_back(uID);
		}

		void PhySprite::Update()
		{
			if (m_Body && GetSprite())
			{
				b2Vec2 bodyPos = m_Body->GetPosition();

				GetSprite()->SetPosition(Vec2(bodyPos.x - GetWidth() / 2,
					bodyPos.y - GetHeight() / 2));

				GetSprite()->SetAngle(n2dRadToDeg(m_Body->GetAngle()));
			}
		}

		int PhySprite::GetWidth() const
		{
			return m_PhySize.x;
		}

		int PhySprite::GetHeight() const
		{
			return m_PhySize.y;
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

			if (!GetPhySprite())
			{
				LOG(LVL_NFE, "Tryinig to create a physics sprite with no sprite.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
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

			if (!GetPhySprite())
			{
				LOG(LVL_NFE, "Tryinig to create a physics sprite with no sprite.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			bodyDef.position.Set(GetX() - GetWidth(), GetY() - GetHeight());

			m_Body = world->CreateBody(&bodyDef);

			b2PolygonShape shape;
			shape.SetAsBox(GetWidth() / 2 * PHYSICS_SCALE, GetHeight() / 2 * PHYSICS_SCALE);

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_CircleShape = false;
			m_RectShape = true;

		}

		void PhySprite::ConfigurePhysicsCircle(bool staticBody, float radius, float density, float friction)
		{
			b2World* world = n2dCurrentPhyWorld();

			if (!world)
			{
				LOG(LVL_NFE, "Tryinig to create a physics body when no physics world is present.");
				return;
			}

			if (!GetPhySprite())
			{
				LOG(LVL_NFE, "Tryinig to create a physics sprite with no sprite.");
				return;
			}

			if (m_Body)
				world->DestroyBody(m_Body);

			b2BodyDef bodyDef;
			bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			bodyDef.position.Set((GetX() + GetWidth()), (GetY() + GetHeight()));

			m_Body = world->CreateBody(&bodyDef);

			b2CircleShape shape;
			shape.m_radius = radius * PHYSICS_SCALE;

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_CircleShape = true;
			m_RectShape = false;

		}

		void PhySprite::ConfigurePhysicsSensorCircle(bool staticBody, float radius, float density, float friction)
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
			bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
			bodyDef.type = staticBody ? b2_staticBody : b2_dynamicBody;
			bodyDef.position.Set((GetX() + GetWidth()/2), (GetY() + GetHeight()/2));

			m_Body = world->CreateBody(&bodyDef);

			b2CircleShape shape;
			shape.m_radius = radius * PHYSICS_SCALE;

			b2FixtureDef fixtureDef;
			fixtureDef.shape = &shape;
			fixtureDef.isSensor = true;
			fixtureDef.density = density;
			fixtureDef.friction = friction;

			m_Body->CreateFixture(&fixtureDef);
			m_CircleShape = true;
			m_RectShape = false;

		}

		void PhySprite::ApplyForce(float force, Directions direction)
		{
			if (m_Body)
			{
				b2Vec2 forceDirection;
				switch (direction)
				{
				case Directions::Up:
					forceDirection = m_Body->GetWorldVector(b2Vec2(0, -1));
					break;
				case Directions::Down:
					forceDirection = m_Body->GetWorldVector(b2Vec2(0, 1));
					break;
				case Directions::Right:
					forceDirection = m_Body->GetWorldVector(b2Vec2(1, 0));
					break;
				case Directions::Left:
					forceDirection = m_Body->GetWorldVector(b2Vec2(-1, 0));
					break;
				}

				m_Body->ApplyForce((force * PHYSICS_MULTIPLIER) * forceDirection, m_Body->GetWorldCenter(), true);
				
			}
		}

		void PhySprite::ApplyAngularForce(float force)
		{
			if (m_Body)
			{
				m_Body->ApplyAngularImpulse(force * (PHYSICS_MULTIPLIER / 30), true);
			}
		}

		void PhySprite::SetScale(float factor)
		{
			if (m_Body)
			{
				b2Fixture* f = m_Body->GetFixtureList();
				m_Body->DestroyFixture(f);

				if (m_RectShape && GetPhySprite())
				{
					b2PolygonShape shape;
					shape.SetAsBox(GetPhySprite()->GetWidth() / 2 * PHYSICS_SCALE * factor, 
						GetPhySprite()->GetHeight() / 2 * PHYSICS_SCALE * factor);
					
					m_Body->CreateFixture(&shape, m_Density);
					m_Body->GetFixtureList()->SetDensity(m_Density);
					m_Body->GetFixtureList()->SetFriction(m_Friction);
					m_Body->GetFixtureList()->SetRestitution(m_Restitution);
					m_Body->GetFixtureList()->SetRestitutionThreshold(m_RestitutionThres);
				}
				else if (m_CircleShape)
				{
					b2CircleShape shape;
					shape.m_radius = m_Radius * PHYSICS_SCALE * factor;
					
					m_Body->CreateFixture(&shape, m_Density);
					m_Body->GetFixtureList()->SetDensity(m_Density);
					m_Body->GetFixtureList()->SetFriction(m_Friction);
					m_Body->GetFixtureList()->SetRestitution(m_Restitution);
					m_Body->GetFixtureList()->SetRestitutionThreshold(m_RestitutionThres);
				}
				else
				{
					LOG(LVL_NON_FATAL_ERROR, "Cannot scale polygon shaped bodies.");
					return;
				}

				if (GetSprite())
					GetSprite()->SetScale(factor);
			}
		}

		void PhySprite::SetPosition(Vec2 position)
		{
			if (m_Body)
				m_Body->SetTransform(b2Vec2(position.x + GetWidth() / 2, position.y + GetHeight() / 2),
					m_Body->GetAngle());

			Sprite::SetPosition(position);
		}

		void PhySprite::DestroySelf()
		{
			if (m_Body)
			{
				if (Game::s_SceneManager->GetCurrentWorld())
				{
					Game::s_SceneManager->GetCurrentWorld()->DestroyBody(m_Body);
				}
			}

			CleanUpdaters();
			Sprite::DestroySelf();
		}
	
	}
}