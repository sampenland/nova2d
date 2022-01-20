#include "SceneManager.h"
#include "TypeDefs.h"
#include "../graphics/Renderer.h"

namespace novazero
{
	namespace core
	{
		std::vector<f_VoidFunction> SceneManager::s_Updaters;

		ReferenceManager* SceneManager::s_ReferenceManager;
		CollisionManager* SceneManager::s_CollisionManager;

		SceneManager::SceneManager()
		{
			s_CollisionManager = new CollisionManager();
			s_ReferenceManager = new ReferenceManager();
		}

		SceneManager::~SceneManager()
		{
			if (s_ReferenceManager)
				delete s_ReferenceManager;

			if (s_CollisionManager)
				delete s_CollisionManager;
		}

		void SceneManager::ConfigureFirstScene(std::string sceneName)
		{

		}

		void SceneManager::AddScene(std::string sceneName, Scene* scene)
		{
			m_Scenes[sceneName] = scene;
		}

		void SceneManager::RemoveScene(std::string sceneName)
		{
			m_Scenes.erase(sceneName);
		}

		Scene* SceneManager::GetScene(std::string sceneName)
		{
			if (m_Scenes.find(sceneName) == m_Scenes.end()) return nullptr;
			return m_Scenes[sceneName];
		}

		void SceneManager::ChangeScene(std::string sceneName)
		{
			if (GetScene(sceneName) == nullptr)
			{
				LOG(sceneName);
				LOG("Cannot find scene");
				return;
			}

			s_Updaters.clear();
			s_CollisionManager->ClearColliders();
			Renderer::s_DrawLayers->ClearSprites();

		}
		
		void SceneManager::Update()
		{
			for (size_t i = 0; i < s_Updaters.size(); i++)
			{
				s_Updaters[i]();
			}

			s_CollisionManager->Update();
		}

		void SceneManager::RemoveUpdater(f_VoidFunction updater)
		{
			int idx = -1;
			for (size_t i = 0; i < s_Updaters.size(); i++)
			{
				if (&s_Updaters[i] == &updater)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			s_Updaters.erase(s_Updaters.begin() + idx);

		}

		void SceneManager::AddUpdater(f_VoidFunction updater)
		{
			s_Updaters.push_back(updater);
		}
	}
}