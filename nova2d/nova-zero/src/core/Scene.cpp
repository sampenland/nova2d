#include "Scene.h"
#include "../core/Game.h"

namespace novazero
{
	namespace core
	{
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