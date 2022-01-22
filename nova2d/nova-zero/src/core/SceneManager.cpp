#include "SceneManager.h"
#include "../graphics/Renderer.h"

namespace novazero
{
	namespace core
	{
		std::vector<f_VoidFunction> SceneManager::s_Updaters;
		std::vector<Deleteable*> SceneManager::s_Deleteables;

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
			Scene* loadScene = GetScene(sceneName);
			if (loadScene == nullptr)
			{
				LOG(sceneName);
				LOG("Could not start. No first scene.");
				return;
			}

			m_CurrentScene = loadScene;
			m_CurrentScene->m_Started = true;
			m_CurrentScene->Start();
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
			Scene* loadScene = GetScene(sceneName);
			if (loadScene == nullptr)
			{
				LOG(sceneName);
				LOG("Cannot find scene");
				return;
			}

			m_CurrentScene->Clean();
			m_CurrentScene->CleanUp();
			m_CurrentScene->End();

			s_Updaters.clear();
			s_CollisionManager->ClearColliders();
			Renderer::s_DrawLayers->ClearSprites();

			m_CurrentScene = loadScene;
			
			if(!m_CurrentScene->m_Started) m_CurrentScene->Restart();
			m_CurrentScene->m_Started = true;

			LOG("Starting scene:");
			LOG(m_CurrentScene->m_SceneName);

			m_CurrentScene->Start();

		}

		void SceneManager::Clean()
		{
			std::vector<void*> r;
			for (size_t i = 0; i < s_Deleteables.size(); i++)
			{
				if (s_Deleteables[i]->m_DeleteNow)
				{
					delete s_Deleteables[i];
				}
			}
		}
		
		void SceneManager::Update()
		{
			m_CurrentScene->Update();

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

		void SceneManager::RemoveDeleteable(Deleteable* object)
		{
			int idx = -1;
			for (size_t i = 0; i < s_Deleteables.size(); i++)
			{
				if (&s_Deleteables[i] == &object)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			s_Deleteables.erase(s_Deleteables.begin() + idx);

		}

		void SceneManager::AddDeleteable(Deleteable* object)
		{
			s_Deleteables.push_back(object);
		}
	}
}