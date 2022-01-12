#include "Game.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace core
	{
		using namespace maths;

		Renderer* Game::s_Renderer;

		Game::Game(const Vec2 screenSize, const char* title)
			: m_Width((int)floor(screenSize.x)), m_Height((int)floor(screenSize.y)), 
			m_Title(title)
		{

			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			if (m_MainWindow)
				m_Running = true;
			else
				return;

			s_Renderer = new Renderer(*(m_MainWindow->GetWindow()), Vec4(50, 50, 255, 255));

		}

		void Game::Update()
		{

			s_Renderer->Update();

			SDL_Event event;
			SDL_PollEvent(&event);

			switch (event.type)
			{
			case SDL_QUIT:
				m_Running = false;
				break;
			}
		}

		Game::~Game()
		{
			
			if (m_SceneManager) 
				delete m_SceneManager;

			if (m_MainWindow) 
				delete m_MainWindow;

			if (s_Renderer)
				delete s_Renderer;

			SDL_Quit();

		}
	}
}