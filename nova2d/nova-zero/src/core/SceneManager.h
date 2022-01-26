#pragma once
#include "Scene.h"
#include "TypeDefs.h"
#include "../physics/CollisionManager.h"
#include "../utils/ReferenceManager.h"
#include <map>
#include <string>
#include <vector>
#include "../core/Deleteable.h"

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

		public:
		
			SceneManager();
			~SceneManager();

			void ConfigureFirstScene(std::string sceneName);
			
			void AddScene(std::string sceneName, Scene* scene);
			void RemoveScene(std::string sceneName);
			Scene* GetScene(std::string sceneName);
			void ChangeScene(std::string sceneName);

			void Update();
			void ProcessUpdaters();
			void CleanUpdaters();
			void Clean();

			static ReferenceManager* s_ReferenceManager;
			static CollisionManager* s_CollisionManager;

			static std::map<unsigned int, f_VoidFunction> s_Updaters;
			static std::map<unsigned int, bool> s_UpdaterErasers;
			static std::map<unsigned int, f_VoidFunction> s_UpdatersToAdd;
			static unsigned int AddUpdater(f_VoidFunction updater);
			static void RemoveUpdater(unsigned int id);
			static unsigned int GetUpdaterCount() 
			{ 
				return (unsigned int)s_Updaters.size(); 
			};

			static std::map<unsigned int, Deleteable*> s_Deleteables;
			static unsigned int AddDeleteable(Deleteable* o);
			static void RemoveDeleteable(unsigned int id);

		};
	}
}