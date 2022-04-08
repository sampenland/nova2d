#include "Scene.h"
#include "../core/Game.h"

namespace novazero
{
	namespace core
	{
		PhysicsDebug* Scene::s_PhysicsDrawer = nullptr;
		Environment* Scene::s_Environment = nullptr;

		Scene::Scene(const std::string& sceneName)
			:m_SceneName(sceneName)
		{
			
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

		void Scene::EnablePhysics(bool enabled, Vec2 gravity)
		{
			m_PhysicsEnabled = enabled;
			m_Gravity = new b2Vec2(gravity.x, gravity.y);
			m_World = new b2World(*m_Gravity);

			b2Vec2 lowerLeftCorner = b2Vec2(0, 0);
			b2Vec2 lowerRightCorner = b2Vec2(Game::s_Width, 0);
			b2Vec2 upperLeftCorner = b2Vec2(0, Game::s_Height);
			b2Vec2 upperRightCorner = b2Vec2(Game::s_Width, Game::s_Height);
		
			// static container body, with the collisions at screen borders
			b2BodyDef screenBorderDef;
			screenBorderDef.position.Set(0, 0);
			b2Body* screenBorderBody = m_World->CreateBody(&screenBorderDef);
			
			const int width = 50;
			const int height = 50;
			const int pad = 25;

			b2BodyDef leftDef;
			leftDef.position.Set(-pad, 0);
			b2Body* leftBody = m_World->CreateBody(&leftDef);

			b2BodyDef rightDef;
			rightDef.position.Set(Game::s_Width + pad, 0);
			b2Body* rightBody = m_World->CreateBody(&rightDef);

			b2BodyDef upDef;
			upDef.position.Set(0, -pad);
			b2Body* upBody = m_World->CreateBody(&upDef);

			b2BodyDef downDef;
			downDef.position.Set(0, Game::s_Height + pad);
			b2Body* downBody = m_World->CreateBody(&downDef);

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
				LOG(LVL_NFE, "Couldn't turn on physics debug. Physics not enabled.");
			}
		}

		void Scene::PhysicsStep()
		{
			if (m_PhysicsEnabled)
			{
				if (m_World)
				{
					// Step world
					m_World->Step(m_TimeStep, 8, 3);
				}
			}
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

		void Scene::CleanUp()
		{
			m_CleanUpObjects.clear();
		}
	}
}