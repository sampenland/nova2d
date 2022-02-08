#pragma once
#include "EventListener.h"
#include <functional>
#include <vector>
#include <string>

namespace novazero
{
	namespace core
	{
		class Scene : public EventListener
		{
		
		private:

			std::vector<void*> m_CleanUpObjects;

		public:

			Scene(const std::string& sceneName);

			bool m_Started = false;
			std::string m_SceneName = "";

			virtual void Start() = 0;
			void Restart();
			void Clean();

			virtual void End() = 0;
			virtual void Update() = 0;

			void AddObjectToCleanUp(void* obj);
			void CleanUp();
		};
	}
}