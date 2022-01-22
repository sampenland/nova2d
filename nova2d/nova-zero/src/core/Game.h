#pragma once
#include "../core/Defines.h"
#include "../core/TypeDefs.h"
#include "SDL.h"

#include "../input/InputHandler.h"
#include "../graphics/Window.h"

#include "SceneManager.h"
#include "../utils/ColorManager.h"
#include "../utils/AssetManager.h"
#include "../physics/CollisionManager.h"
#include "../utils/FontManager.h"

#include "../graphics/Color.h"
#include <vector>
#include "../maths/Rect.h"

namespace novazero
{

	namespace graphics
	{
		class Renderer;
	}

	namespace core
	{
		class Game
		{

		private:

			const char FPS = 60;
			const float FRAME_DELAY = 1000.0f / FPS;
			Uint32 frameStart = 0;
			int frameTime = 0;
			Uint64 NOW;
			Uint64 LAST;

			const char* m_Title = {};
			
			novazero::graphics::Window* m_MainWindow = nullptr;
			novazero::core::SceneManager* m_SceneManager = nullptr;

		public:

			Game(const novazero::maths::Vec2Int screenSize, const char* title);
			~Game();

			void Tick();

			void Process();
			void Update();
			void PollEvents();
			void Render();
			void Clean();

			void ConfigureFirstScene(std::string sceneName);
			void ConfigureIcon(const char* iconPath) { m_MainWindow->ConfigureIcon(iconPath); }

		public:

			static novazero::graphics::Renderer* s_Renderer;
			static novazero::utils::ColorManager* s_ColorManager;
			static novazero::input::InputHandler* s_InputHandler;
			static novazero::utils::AssetManager* s_AssetManager;
			static SceneManager* s_SceneManager;
			static novazero::utils::FontManager* s_FontManager;

			static double s_DeltaTime;
			static double GetDeltaTime() { return s_DeltaTime; }

			static int s_Width;
			static int s_Height;
			static int s_Padding;

			static novazero::maths::Rect GetGameBounds();
			static void SetGamePadding(int padding);
			
			static unsigned int s_IDCount;
			static unsigned int GetNextID() { s_IDCount++; return s_IDCount; }

			static unsigned int s_Score;
			static unsigned int AddScore(unsigned int add) { s_Score += add; return s_Score; }
			static unsigned int GetScore() { return s_Score; }
			static void SetScore(unsigned int score) { s_Score = score; }

			static bool s_Running;
			static bool IsRunning() { return s_Running; }
			static int s_ExitCode;
			static void EndGame(int exitCode)
			{
				s_ExitCode = exitCode;
				s_Running = false;
			}
		};
	}
}