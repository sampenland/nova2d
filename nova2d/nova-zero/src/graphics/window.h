#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "Renderer.h"
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		class Window
		{

		private:

			SDL_GLContext m_GlContext;
			SDL_Window* m_Window;
			SDL_Surface* m_Icon;
			
			int m_Width;
			int m_Height;
			
			const char* m_Title;

		public:

			Window(const Vec2Int screenSize, const char* title);

			void Init();
			void ConfigureIcon(const char* path)
			{
				if (m_Window)
				{
					m_Icon = IMG_Load(path);
					SDL_SetWindowIcon(m_Window, m_Icon);
				}
				
			}

			void SetupImGUI(SDL_Renderer* render);

			SDL_Window* GetWindow() const;
			SDL_GLContext GetGLContext() const
			{
				return m_GlContext;
			}
			
			void DestroySelf();

		};
	}
}