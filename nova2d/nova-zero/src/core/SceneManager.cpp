#include "SceneManager.h"
#include "TypeDefs.h"

namespace novazero
{
	namespace core
	{
		std::vector<f_VoidFunction> SceneManager::s_EventSteppers;
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

		void SceneManager::RemoveEventStepper(f_VoidFunction eventStep)
		{
			int idx = -1;
			for (size_t i = 0; i < s_EventSteppers.size(); i++)
			{
				if (&s_EventSteppers[i] == &eventStep)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			s_EventSteppers.erase(s_EventSteppers.begin() + idx);

		}

		void SceneManager::AddEventStepper(f_VoidFunction eventStep)
		{
			s_EventSteppers.push_back(eventStep);
		}

		void SceneManager::RemoveUpdater(f_VoidFunction updater)
		{
			int idx = -1;
			for (size_t i = 0; i < s_Updaters.size(); i++)
			{
				if (&s_EventSteppers[i] == &updater)
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
			s_EventSteppers.push_back(updater);
		}
	}
}