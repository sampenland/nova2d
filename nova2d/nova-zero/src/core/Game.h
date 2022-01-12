#pragma once
#include "../maths/Vec2.h"
#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../graphics/Renderer.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;

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

			Game(const Vec2 screenSize, const char* title);
			~Game();

			inline bool IsRunning() const { return m_Running; }

			void Update();
			void PollEvents();

		public:
			static Renderer* s_Renderer;
		};
	}
}