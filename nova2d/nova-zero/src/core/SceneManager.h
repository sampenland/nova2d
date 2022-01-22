#pragma once
#include "Scene.h"
#include "TypeDefs.h"
#include "../physics/CollisionManager.h"
#include "../utils/ReferenceManager.h"
#include "Destructor.h"
#include <map>
#include <string>

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
			void Clean();

			static ReferenceManager* s_ReferenceManager;
			static CollisionManager* s_CollisionManager;

			static std::vector<f_VoidFunction> s_Updaters;
			static std::vector<Destructor*> s_Destructors;
			static void AddUpdater(f_VoidFunction updater, Destructor* updaterSelf);
			static void RemoveUpdater(f_VoidFunction updater, Destructor* updaterSelf);

		};
	}
}