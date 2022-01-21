#include "Scene.h"

namespace novazero
{
	namespace core
	{
		Scene::Scene(std::string sceneName)
			:m_SceneName(sceneName)
		{
			
		}

		Scene::~Scene()
		{

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