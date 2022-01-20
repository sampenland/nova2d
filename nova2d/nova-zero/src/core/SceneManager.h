#pragma once
#include "Scene.h"

namespace novazero
{
	namespace core
	{
		class SceneManager
		{
		
		private:
		
			Scene* m_FirstScene = nullptr;

		public:
		
			SceneManager();
			~SceneManager();

			void ConfigureFirstScene(Scene* firstScene) { m_FirstScene = firstScene; }

			void Update();

		};
	}
}