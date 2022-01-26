#include "Window.h"
#include "../logging/Logging.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		Window::Window(const Vec2Int screenSize, const char* title)
			: m_Title(title)
		{
			m_Width = (int)floor(screenSize.x);
			m_Height = (int)floor(screenSize.y);

			Init();
		}

		Window::~Window()
		{
			if (m_Icon)
				SDL_FreeSurface(m_Icon);
			
			m_Icon = NULL;
			SDL_DestroyWindow(m_Window);
		}

		void Window::Init()
		{
			using namespace logging;
			
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) != 0) {
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
				
			}
			else
			{
				std::string err = SDL_GetError();
				LOG(LVL_FATAL_ERROR, "Could not create window: " + err);
				return;
			}

		}

		SDL_Window* Window::GetWindow() const
		{
			return m_Window;
		}
	}
}