#include "window.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace graphics
	{
		Window::Window(const char* title)
			: m_Title(title)
		{
			Init();
		}

		Window::~Window()
		{
			SDL_DestroyWindow(m_Window);
			SDL_Quit();
		}

		void Window::Init()
		{
			using namespace logging;
			
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
				SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
				return;
			}

			m_Window = SDL_CreateWindow(
				m_Title,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				640,
				480,
				SDL_WINDOW_OPENGL
			);

			if (m_Window)
			{

			}
			else
			{
				LOG("Could not create winodw:");
				LOG(SDL_GetError());
				return;
			}

		}
	}
}