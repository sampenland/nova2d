#pragma once
#include "Scene.h"
#include "TypeDefs.h"
#include "../physics/CollisionManager.h"
#include "../utils/ReferenceManager.h"
#include <map>
#include <string>
#include <vector>
#include "../core/Deleteable.h"
#include "../physics/GraverManager.h"
#include "../utils/TweenManager.h"
#include "../physics/TimeEffectorManager.h"

namespace novazero
{
	namespace physics
	{
		class CollisionManager;
	}

	namespace core
	{
		using namespace utils;
		using namespace physics;

		class SceneManager
		{
		
		private:
		
			std::map<std::string, Scene*> m_Scenes;
			Scene* m_CurrentScene = nullptr;
			bool m_Destroyed = false;

		public:

			std::string m_LastSceneName = "none";
			std::string m_CurrentSceneName = "none";

		public:
		
			SceneManager();

			void ConfigureFirstScene(const std::string& sceneName);
			
			void AddScene(const std::string& sceneName, Scene* scene);
			void RemoveScene(const std::string& sceneName);
			Scene* GetScene(const std::string& sceneName);
			void ChangeScene(const std::string& sceneName);

			void Update();
			void ProcessUpdaters();
			void ProcessPersistentUpdaters();
			void CleanUpdaters();
			void Clean();

			void DestroySelf();

			static ReferenceManager* s_ReferenceManager;
			static CollisionManager* s_CollisionManager;
			static GraverManager* s_GraverManager;
			static TweenManager* s_TweenManager;
			static TimeEffectorManager* s_TimeEffectorManager;

			static std::map<unsigned int, std::function<void()>> s_Updaters;
			static std::map<unsigned int, bool> s_UpdaterErasers;
			static std::map<unsigned int, std::function<void()>> s_UpdatersToAdd;
			static unsigned int AddUpdater(std::function<void()> updater);
			static void RemoveUpdater(unsigned int id);
			static unsigned int GetUpdaterCount() 
			{ 
				return (unsigned int)s_Updaters.size(); 
			};

			static std::map<unsigned int, std::function<void()>> s_PersistentUpdaters;
			static std::map<unsigned int, bool> s_PersistentUpdaterErasers;
			static std::map<unsigned int, std::function<void()>> s_PersistentUpdatersToAdd;
			static unsigned int AddPersistentUpdater(std::function<void()> persistentUpdater);
			static void RemovePersistentUpdater(unsigned int id);
			static unsigned int GetPersistentUpdaterCount()
			{
				return (unsigned int)s_PersistentUpdaters.size();
			};

			static std::map<unsigned int, Deleteable*> s_Deleteables;
			static unsigned int AddDeleteable(Deleteable* o);
			static void RemoveDeleteable(unsigned int id);
			static unsigned int GetDeleteableCount()
			{
				return (unsigned int)s_Deleteables.size();
			};

		};
	}
}