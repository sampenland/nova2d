#pragma once
#include "../core/Defines.h"
#include "../core/TypeDefs.h"
#include "SDL.h"
//#include <vector>
//#include <functional>

#include "../input/InputHandler.h"
#include "../graphics/Window.h"

#include "SceneManager.h"
#include "../utils/ColorManager.h"
#include "../utils/AssetManager.h"
#include "../physics/CollisionManager.h"

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

			bool m_Running = false;
			const char* m_Title = {};
			
			novazero::graphics::Window* m_MainWindow = nullptr;
			novazero::core::SceneManager* m_SceneManager = nullptr;

		public:

			Game(const novazero::maths::Vec2Int screenSize, const char* title);
			~Game();

			inline bool IsRunning() const { return m_Running; }

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

			static double s_DeltaTime;
			static int s_Width;
			static int s_Height;
			static int s_Padding;

			static novazero::maths::Rect GetGameBounds();
			static void SetGamePadding(int padding);
			
			static unsigned int s_IDCount;
			static unsigned int GetNextID() { s_IDCount++; return s_IDCount; }
		};
	}
}