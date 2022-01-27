#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include <algorithm>
#include "Game.h"

namespace novazero
{
	namespace core
	{
		std::map<unsigned int, f_VoidFunction> SceneManager::s_Updaters;
		std::map<unsigned int, bool> SceneManager::s_UpdaterErasers;
		std::map<unsigned int, f_VoidFunction> SceneManager::s_UpdatersToAdd;
		std::map<unsigned int, Deleteable*> SceneManager::s_Deleteables;

		ReferenceManager* SceneManager::s_ReferenceManager;
		CollisionManager* SceneManager::s_CollisionManager;

		SceneManager::SceneManager()
		{
			s_CollisionManager = new CollisionManager();
			s_ReferenceManager = new ReferenceManager();
			s_GraverManager = new GraverManager();
		}

		SceneManager::~SceneManager()
		{
			if (s_ReferenceManager)
				delete s_ReferenceManager;

			if (s_CollisionManager)
				delete s_CollisionManager;

			if (s_GraverManager)
				delete s_GraverManager;
		}

		void SceneManager::ConfigureFirstScene(std::string sceneName)
		{
			Scene* loadScene = GetScene(sceneName);
			if (loadScene == nullptr)
			{
				LOG(LVL_FATAL_ERROR, "Could not start. No first scene: " + sceneName);
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
				LOG(LVL_NON_FATAL_ERROR, "Cannot find scene: " + sceneName);
				return;
			}

			m_CurrentScene->Clean();
			m_CurrentScene->CleanUp();
			m_CurrentScene->End();

			CleanUpdaters();
			s_CollisionManager->ClearColliders();
			Renderer::s_DrawLayers->ClearSprites();
			s_Deleteables.clear();

			m_CurrentScene = loadScene;
			
			if(!m_CurrentScene->m_Started) m_CurrentScene->Restart();
			m_CurrentScene->m_Started = true;

			LOG(LVL_INFO, "Starting scene: " + m_CurrentScene->m_SceneName);

			m_CurrentScene->Start();

			if (Game::s_DebugOverlay)
			{
				Game::ConfigureDebug(true);
				Game::ConfigureDebugPosition(Vec2Int(32, 32));
			}

		}

		void SceneManager::CleanUpdaters()
		{
			// mark all updaters to be removed
			std::map<unsigned int, f_VoidFunction>::iterator it = s_Updaters.begin();
			while (it != s_Updaters.end())
			{
				s_UpdaterErasers[it->first] = true;
				it++;
			}
		}

		void SceneManager::Clean()
		{
			std::map<unsigned int, Deleteable*>::iterator it = s_Deleteables.begin();
			std::vector<unsigned int> removeIDs;
			for (it; it != s_Deleteables.end(); it++)
			{
				if (it->second->m_DeleteNow == 1)
				{
					removeIDs.push_back(it->first);
					delete it->second;
				}
			}

			for (size_t i = 0; i < removeIDs.size(); i++)
			{
				s_Deleteables.erase(removeIDs[i]);
			}
		}
		
		void SceneManager::Update()
		{
			m_CurrentScene->Update();

			ProcessUpdaters();

			s_CollisionManager->Update();
		}

		void SceneManager::ProcessUpdaters()
		{
			// Add new updaters
			std::map<unsigned int, f_VoidFunction>::iterator itA = s_UpdatersToAdd.begin();
			while (itA != s_UpdatersToAdd.end())
			{
				s_Updaters[itA->first] = itA->second;
				s_UpdaterErasers[itA->first] = false;
				itA++;
			}

			s_UpdatersToAdd.clear();

			// Remove any removed updaters
			std::map<unsigned int, bool>::iterator it = s_UpdaterErasers.begin();
			while (it != s_UpdaterErasers.end())
			{
				if (it->second)
				{
					s_Updaters.erase(it->first);
				}

				it++;
			}

			s_UpdaterErasers.clear();

			// Update
			std::map<unsigned int, f_VoidFunction>::iterator it2 = s_Updaters.begin();
			for (; it2 != s_Updaters.end(); ++it2)
			{
				if (it2->second)
				{
					it2->second();
				}
 			}
		}

		void SceneManager::RemoveUpdater(unsigned int id)
		{
			s_UpdaterErasers[id] = true;
		}

		unsigned int SceneManager::AddUpdater(f_VoidFunction updater)
		{
			unsigned int id = n2dGameGetID();
			s_UpdatersToAdd[id] = updater;
			return id;
		}

		void SceneManager::RemoveDeleteable(unsigned int id)
		{
			s_Deleteables.erase(id);
		}

		unsigned int SceneManager::AddDeleteable(Deleteable* object)
		{
			unsigned int id = n2dGameGetID();
			s_Deleteables[id] = object;
			return id;
		}
	}
}