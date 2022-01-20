#include "SceneManager.h"
#include "TypeDefs.h"

namespace novazero
{
	namespace core
	{
		std::vector<f_VoidFunction> SceneManager::s_Updaters;

		ReferenceManager* SceneManager::s_ReferenceManager;
		CollisionManager* SceneManager::s_CollisionManager;

		SceneManager::SceneManager()
		{
			s_ReferenceManager = new ReferenceManager();
		}

		SceneManager::~SceneManager()
		{
			if (s_ReferenceManager)
				delete s_ReferenceManager;

			if (s_CollisionManager)
				delete s_CollisionManager;
		}
		
		void SceneManager::Update()
		{

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