#pragma once
#include "../maths/Vec2.h"
#include "../graphics/Window.h"
#include "SceneManager.h"
#include "../graphics/Renderer.h"
#include "../utils/ColorManager.h"
#include "../graphics/Color.h"
#include "../input/InputHandler.h"
#include "EventListener.h"
#include <vector>

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;
		using namespace utils;
		using namespace input;

		class Game
		{

		private:

			const char FPS = 60;
			const float FRAME_DELAY = 1000.0f / FPS;
			Uint32 frameStart = 0;
			int frameTime = 0;

			bool m_Running = false;
			const char* m_Title = {};
			
			Window* m_MainWindow = nullptr;
			SceneManager* m_SceneManager = nullptr;

			std::vector<EventListener> m_EventListeners;

		public:

			Game(const Vec2 screenSize, const char* title, const Color backgroundColor = Color(0, 0, 0, 255));
			~Game();

			inline bool IsRunning() const { return m_Running; }

			void Tick();

			void Process();
			void Update();
			void PollEvents();
			void Render();
			void Clean();

			void AddEventListerInstance(EventListener listener);
			void RemoveEventListenerInstance(EventListener listener);

		public:

			static Renderer* s_Renderer;
			static ColorManager* s_ColorManager;
			static InputHandler* s_InputHandler;
			static unsigned int s_IDCount;
			static int s_Width;
			static int s_Height;
		};
	}
}