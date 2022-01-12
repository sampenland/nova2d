#pragma once
#include "../maths/Vec2.h"
#include "../graphics/Window.h"
#include "SceneManager.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;

		class Game
		{

		private:
			bool m_Running = false;
			int m_Width = 0;
			int m_Height = 0;
			const char* m_Title = {};

			Window* m_MainWindow = nullptr;
			SceneManager* m_SceneManager = nullptr;

		public:

			Game(const maths::vec2 screenSize, const char* title);
			~Game();

			void Update();
		};
	}
}