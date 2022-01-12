#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace graphics
	{
		class Window
		{

		private:

			SDL_Window* m_Window;
			Renderer* m_Renderer;
			
			int m_Width;
			int m_Height;
			
			const char* m_Title;

		public:

			Window(const maths::vec2 screenSize, const char* title);
			~Window();

			void Init();

		};
	}
}