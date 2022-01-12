#pragma once
#include "SDL.h"

namespace novazero
{
	namespace graphics
	{
		class Window
		{

		private:

			SDL_Window* m_Window;
			const char* m_Title;

		public:
			Window(const char* title);
			~Window();

			void Init();

		};
	}
}