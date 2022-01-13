#pragma once
#include "../maths/Vec2.h"
#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include "../utils/ColorManager.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;
		using namespace utils;

		class Game
		{

		private:

			const char FPS = 60;
			const float FRAME_DELAY = 1000 / FPS;
			Uint32 frameStart = 0;
			int frameTime = 0;

			bool m_Running = false;
			int m_Width = 0;
			int m_Height = 0;
			const char* m_Title = {};
			
			Window* m_MainWindow = nullptr;
			SceneManager* m_SceneManager = nullptr;

		public:

			Game(const Vec2 screenSize, const char* title, const Vec4 backgroundColor = Vec4(0, 0, 0, 255));
			~Game();

			inline bool IsRunning() const { return m_Running; }

			void Update();
			void PollEvents();

		public:
			static Renderer* s_Renderer;
			static ColorManager* s_ColorManager;
		};
	}
}