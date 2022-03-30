#pragma once
#include "EventListener.h"
#include "../maths/Vec2.h"
#include <functional>
#include <vector>
#include <string>

namespace novazero
{
	namespace core
	{
		using namespace novazero::maths;

		class Scene : public EventListener
		{
		
		private:

			std::vector<void*> m_CleanUpObjects;
			Vec2 m_Gravity = Vec2(0, 0);

		public:

			Scene(const std::string& sceneName);

			bool m_Started = false;
			std::string m_SceneName = "";

			void SetGravity(float x, float y);
			Vec2 GetGravity() const { return m_Gravity; }

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