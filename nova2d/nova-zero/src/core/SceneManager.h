#pragma once
#include "Scene.h"
#include "../utils/ReferenceManager.h"
#include "../physics/CollisionManager.h"

namespace novazero
{
	namespace core
	{
		using namespace utils;
		using namespace physics;

		class SceneManager
		{
		
		private:
		
			Scene* m_FirstScene = nullptr;
			Scene* m_CurrentScene = nullptr;

		public:
		
			SceneManager();
			~SceneManager();

			void ConfigureFirstScene(Scene* firstScene) { m_FirstScene = firstScene; m_CurrentScene = firstScene; }

			void ChangeScene(Scene* toScene);

			void Update();

			static ReferenceManager* s_ReferenceManager;
			static CollisionManager* s_CollisionManager;

			static std::vector<f_VoidFunction> s_Updaters;
			static void AddUpdater(f_VoidFunction updater);
			static void RemoveUpdater(f_VoidFunction updater);

		};
	}
}