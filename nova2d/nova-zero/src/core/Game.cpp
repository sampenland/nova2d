#include "Game.h"

namespace novazero
{
	namespace core
	{
		Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;

		// --------------------------------

		Game::Game(const Vec2 screenSize, const char* title, const Color backgroundColor)
			: m_Width((int)floor(screenSize.x)), m_Height((int)floor(screenSize.y)), 
			m_Title(title)
		{

			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			if (m_MainWindow)
				m_Running = true;
			else
				return;

			s_ColorManager = new ColorManager();
			s_Renderer = new Renderer(*(m_MainWindow->GetWindow()), backgroundColor);
			m_InputHandler = new InputHandler();			

		}

		void Game::PollEvents()
		{
			SDL_Event event;
			SDL_PollEvent(&event);

			switch (event.type)
			{
			case SDL_KEYDOWN:
				m_InputHandler->KeyDown(&event);
				break;

			case SDL_KEYUP:
				m_InputHandler->KeyUp(&event);
				break;
			case SDL_QUIT:
				m_Running = false;
				break;
			}
		}

		void Game::Tick()
		{
			// FPS handling
			frameStart = SDL_GetTicks();
			// ----------------

			Update();
			Render();
			Clean();

			// FPS handling
			frameTime = SDL_GetTicks() - frameStart;
			if (FRAME_DELAY > frameTime)
			{
				SDL_Delay(FRAME_DELAY - frameTime);
			}
			// -----------------
		}

		void Game::Render()
		{
			s_Renderer->PreDraw();
		}

		void Game::Clean()
		{

		}

		void Game::Update()
		{
			PollEvents();
		}

		Game::~Game()
		{
			
			if (m_SceneManager) 
				delete m_SceneManager;

			if (m_MainWindow) 
				delete m_MainWindow;

			if (s_Renderer)
				delete s_Renderer;

			if (s_ColorManager)
				delete s_ColorManager;

			if (m_InputHandler)
				delete m_InputHandler;

			SDL_Quit();

		}
	}
}