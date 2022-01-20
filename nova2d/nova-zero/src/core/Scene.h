#pragma once
#include <functional>
#include <vector>

namespace novazero
{
	namespace core
	{
		class Scene
		{
		
		private:

			std::vector<void*> m_CleanUpObjects;

		public:

			Scene() { };

			virtual void Start() = 0;
			virtual void End() = 0;
			virtual void Update() = 0;

			void AddObjectToCleanUp(void* obj)
			{
				m_CleanUpObjects.push_back(obj);
			}

			void CleanUp()
			{
				m_CleanUpObjects.clear();
			}

		};
	}
}