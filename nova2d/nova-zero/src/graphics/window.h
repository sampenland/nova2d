#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		class Window
		{

		private:

			SDL_Window* m_Window;
			
			int m_Width;
			int m_Height;
			
			const char* m_Title;

		public:

			Window(const Vec2 screenSize, const char* title);
			~Window();

			void Init();

			SDL_Window* GetWindow() const;

		};
	}
}