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
#include "../utils/SQLManager.h"
#include "../debug/DebugOverlay.h"

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
			void ConfigureSQL(std::string databaseName, std::string connectionString, std::string user, std::string pass, bool useNovaSQLScoring);

		public:

			static novazero::graphics::Renderer* s_Renderer;
			static novazero::utils::ColorManager* s_ColorManager;
			static novazero::input::InputHandler* s_InputHandler;
			static novazero::utils::AssetManager* s_AssetManager;
			static SceneManager* s_SceneManager;
			static novazero::utils::FontManager* s_FontManager;
			static novazero::utils::SQLManager* s_SQLManager;
			static novazero::debug::DebugOverlay* s_DebugOverlay;

			static void ConfigureDebug(bool isVisible);
			// Must call ConfigureDebug(true) before this works
			static void ConfigureDebugPosition(Vec2Int pos) { if (s_DebugOverlay) { s_DebugOverlay->SetPosition(pos); } }


			static double s_DeltaTime;
			static double GetDeltaTime() { return s_DeltaTime; }
			static double s_FPS;

			static int s_Width;
			static int s_Height;
			static int s_Padding;

			static novazero::maths::Rect GetGameBounds(int paddingOverride = 0);
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

			static float RandomFloat(float min, float max)
			{
				return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
			}
			static int RandomInt(int min, int max)
			{
				// Random int between min-max
				return (int)(rand() % min + max);
			}
		};
	}
}