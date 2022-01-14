#include "Game.h"

namespace novazero
{
	namespace core
	{
		Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;
		InputHandler* Game::s_InputHandler;
		unsigned int Game::s_IDCount;
		int Game::s_Width;
		int Game::s_Height;

		// --------------------------------

		Game::Game(const Vec2 screenSize, const char* title, const Color backgroundColor)
			: m_Title(title), m_EventListeners(1)
		{

			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			if (m_MainWindow)
				m_Running = true;
			else
				return;

			s_ColorManager = new ColorManager();
			s_Renderer = new Renderer(*(m_MainWindow->GetWindow()), backgroundColor);
			s_InputHandler = new InputHandler();

			s_Width = (int)floor(screenSize.x);
			s_Height = (int)floor(screenSize.y);

		}

		void Game::PollEvents()
		{
			SDL_Event event;
			SDL_PollEvent(&event);

			switch (event.type)
			{
			case SDL_KEYDOWN:
				s_InputHandler->KeyDown(&event);
				break;

			case SDL_KEYUP:
				s_InputHandler->KeyUp(&event);
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
				SDL_Delay((Uint32)(FRAME_DELAY - frameTime));
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

		void Game::Process()
		{
			for (size_t i = 0; i < m_EventListeners.size(); i++) 
			{
				m_EventListeners[i].EventStep();
			}
		}

		void Game::Update()
		{
			Process();
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

			if (s_InputHandler)
				delete s_InputHandler;

			SDL_Quit();

		}

		void Game::AddEventListerInstance(EventListener listener)
		{
			m_EventListeners.push_back(listener);
		}

		void Game::RemoveEventListenerInstance(EventListener listener)
		{
			int idx = -1;
			for (size_t i = 0; i < m_EventListeners.size(); i++)
			{
				if (m_EventListeners[i] == listener)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			m_EventListeners.erase(m_EventListeners.begin() + idx);

		}
	}
}