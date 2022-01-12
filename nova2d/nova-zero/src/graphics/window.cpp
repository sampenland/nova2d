#include "Window.h"
#include "../maths/Vec2.h"
#include "../logging/Logging.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		Window::Window(const vec2 screenSize, const char* title)
			: m_Title(title)
		{
			m_Width = (int)floor(screenSize.x);
			m_Height = (int)floor(screenSize.y);

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
				m_Width,
				m_Height,
				SDL_WINDOW_OPENGL
			);

			if (m_Window)
			{
				m_Renderer = new Renderer(*m_Window);
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