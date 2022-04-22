#include "Scene.h"
#include "../core/Game.h"
#include "../particles/ParticleSystem.h"

namespace novazero
{
	namespace core
	{
		PhysicsDebug* Scene::s_PhysicsDrawer = nullptr;
		Environment* Scene::s_Environment = nullptr;
		std::map<std::string, ParticleSystem*> Scene::s_ParticleSystems;

		Scene::Scene(const std::string& sceneName)
			:m_SceneName(sceneName)
		{
			*m_TimeStep = 1.f / 60.f;
		}

		void Scene::EnableLights(Uint8 worldLightIntensity)
		{
			static bool initted = false;
			if (initted)
			{
				(*s_Environment->m_WorldLightingIntensity) = worldLightIntensity;
				return;
			}

			s_Environment = new Environment(worldLightIntensity);
			Game::s_Director->InitLighting();
		}

		void Scene::EnablePhysics(bool enabled, Vec2 gravity, float innerPadding)
		{
			m_PhysicsEnabled = enabled;
			m_Gravity = new b2Vec2(gravity.x, gravity.y);
			m_World = new b2World(*m_Gravity);

			m_ContactListener = new PhyContactListener();
			m_World->SetContactListener(m_ContactListener);

			b2Vec2 lowerLeftCorner = b2Vec2(0.f, 0.f);
			b2Vec2 lowerRightCorner = b2Vec2((float)Game::s_Width, 0.f);
			b2Vec2 upperLeftCorner = b2Vec2(0.f, (float)Game::s_Height);
			b2Vec2 upperRightCorner = b2Vec2((float)Game::s_Width, (float)Game::s_Height);
			
			b2BodyDef leftDef;
			leftDef.position.Set(-100 + innerPadding, 0);

			b2PolygonShape leftShape;
			leftShape.SetAsBox(100.f, (float)Game::s_Height);
			leftDef.type = b2_staticBody;

			b2Body* leftBody = m_World->CreateBody(&leftDef);
			leftBody->CreateFixture(&leftShape, 1.0f);

			// ----------------------------------------

			b2BodyDef rightDef;
			rightDef.position.Set((float)Game::s_Width + 100.f - innerPadding, 0.f);

			b2PolygonShape rightShape;
			rightShape.SetAsBox(100.f, (float)Game::s_Height);
			rightDef.type = b2_staticBody;

			b2Body* rightBody = m_World->CreateBody(&rightDef);
			rightBody->CreateFixture(&rightShape, 1.0f);

			// ----------------------------------------

			b2BodyDef upDef;
			upDef.position.Set(0, -100 + innerPadding);

			b2PolygonShape upShape;
			upShape.SetAsBox((float)Game::s_Width, 100);
			upDef.type = b2_staticBody;

			b2Body* upBody = m_World->CreateBody(&upDef);
			upBody->CreateFixture(&upShape, 1.0f);

			// ----------------------------------------

			b2BodyDef downDef;
			downDef.position.Set(0.f, (float)Game::s_Height + 100.f - innerPadding);

			b2PolygonShape downShape;
			downShape.SetAsBox((float)Game::s_Width, 100);
			downDef.type = b2_staticBody;

			b2Body* downBody = m_World->CreateBody(&downDef);
			downBody->CreateFixture(&downShape, 1.0f);			

		}

		void Scene::PhysicsEnableDebug(bool isDebug)
		{
			m_DebugDraw = isDebug;

			if (m_World)
			{
				s_PhysicsDrawer = new PhysicsDebug();
				m_World->SetDebugDraw(s_PhysicsDrawer);
			}
			else
			{
				LOG(LVL_NFE, "Couldn't turn on physics debug. Physics not enabled.", __FILE__, __LINE__);
			}
		}

		void Scene::PhysicsStep()
		{
			// Step world
			m_World->Step(*m_TimeStep, 8, 3);
		}

		b2World* Scene::GetWorld() const
		{
			return m_World;
		}

		void Scene::Restart()
		{
			StartEventListener();
		}

		void Scene::Clean()
		{
			m_Started = false;
			EndEventListener();
		}

		void Scene::AddObjectToCleanUp(void* obj)
		{
			m_CleanUpObjects.push_back(obj);
		}

		void Scene::UpdateParticles()
		{
			for (auto system : s_ParticleSystems)
			{
				system.second->Update();
			}
		}

		void Scene::AddParticleSystem(const std::string& assetName, Vec2Int size, 
			const std::string& systemName, int32 maxParticles, float particleRadius, unsigned char layer)
		{
			ParticleSystem* ps = new ParticleSystem(assetName, size, maxParticles, particleRadius, layer);
			s_ParticleSystems[systemName] = ps;
		}

		ParticleSystem* Scene::GetParticleSystem(const std::string& systemName)
		{
			if (s_ParticleSystems.find(systemName) != s_ParticleSystems.end())
			{
				return s_ParticleSystems[systemName];
			}
			
			return nullptr;
		}

		void Scene::RemoveParticleSystem(const std::string& systemName)
		{
			if (s_ParticleSystems.find(systemName) != s_ParticleSystems.end())
			{
				s_ParticleSystems.erase(systemName);
			}
		}

		int32 Scene::GetParticleCount()
		{
			int32 cnt = 0;
			for (auto ps : s_ParticleSystems)
			{
				cnt += ps.second->ParticleCount();
			}
			return cnt;
		}

		void Scene::CleanUp()
		{
			m_CleanUpObjects.clear();
		}
	}
}