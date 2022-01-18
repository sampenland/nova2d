#pragma once
#include "../input/InputHandler.h"
#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include "../utils/ColorManager.h"
#include "../graphics/Color.h"
#include "EventListener.h"
#include <vector>
#include "../utils/AssetManager.h"
#include "../maths/Rect.h"
#include "../utils/ReferenceManager.h"
#include "../physics/CollisionManager.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;
		using namespace utils;
		using namespace input;
		using namespace physics;

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
			
			Window* m_MainWindow = nullptr;
			SceneManager* m_SceneManager = nullptr;

		public:

			Game(const Vec2Int screenSize, const char* title, const Color backgroundColor = Color(0, 0, 0, 255));
			~Game();

			inline bool IsRunning() const { return m_Running; }

			void Tick();

			void Process();
			void Update();
			void PollEvents();
			void Render();
			void Clean();

			void ConfigureIcon(const char* iconPath) { m_MainWindow->ConfigureIcon(iconPath); }

		public:

			static Renderer* s_Renderer;
			static ColorManager* s_ColorManager;
			static InputHandler* s_InputHandler;
			static AssetManager* s_AssetManager;
			static ReferenceManager* s_ReferenceManager;
			static CollisionManager* s_CollisionManager;

			static double s_DeltaTime;
			static int s_Width;
			static int s_Height;
			static int s_Padding;
			
			static std::vector<f_VoidFunction> s_EventSteppers;
			static void AddEventStepper(f_VoidFunction eventStep);
			static void RemoveEventStepper(f_VoidFunction eventStep);
			
			static std::vector<f_VoidFunction> s_Updaters;
			static void AddUpdater(f_VoidFunction updater);
			static void RemoveUpdater(f_VoidFunction updater);

			static Rect GetGameBounds();
			static void SetGamePadding(int padding);
			
			static unsigned int s_IDCount;
			static unsigned int GetNextID() { s_IDCount++; return s_IDCount; }
		};
	}
}