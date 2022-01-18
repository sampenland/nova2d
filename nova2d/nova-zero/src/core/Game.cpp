#include "Game.h"

namespace novazero
{
	namespace core
	{
		using namespace maths;

		// --------
		std::vector<f_VoidFunction> Game::s_EventSteppers;
		std::vector<f_VoidFunction> Game::s_Updaters;

		Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;
		InputHandler* Game::s_InputHandler;
		AssetManager* Game::s_AssetManager;
		ReferenceManager* Game::s_ReferenceManager;
		CollisionManager* Game::s_CollisionManager;

		unsigned int Game::s_IDCount;
		int Game::s_Width;
		int Game::s_Height;
		double Game::s_DeltaTime;
		int Game::s_Padding;

		// --------------------------------

		Game::Game(const Vec2Int screenSize, const char* title, const Color backgroundColor)
			: m_Title(title)
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
			s_AssetManager = new AssetManager();
			s_ReferenceManager = new ReferenceManager();
			s_CollisionManager = new CollisionManager();

			s_Width = (int)floor(screenSize.x);
			s_Height = (int)floor(screenSize.y);

			NOW = SDL_GetPerformanceCounter();
			LAST = 0;

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
			// ----------------------
			LAST = NOW;
			NOW = SDL_GetPerformanceCounter();
			Game::s_DeltaTime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
			// ----------------

			Process();
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
			s_Renderer->Draw();
			s_Renderer->PostDraw();
		}

		void Game::Clean()
		{

		}

		void Game::Process()
		{
			for (size_t i = 0; i < s_EventSteppers.size(); i++) 
			{
				s_EventSteppers[i]();
			}
			
			for (size_t i = 0; i < s_Updaters.size(); i++) 
			{
				s_Updaters[i]();
			}

			s_CollisionManager->Update();
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

			if (s_AssetManager)
				delete s_AssetManager;

			if (s_ReferenceManager)
				delete s_ReferenceManager;

			SDL_Quit();

		}

		void Game::RemoveEventStepper(f_VoidFunction eventStep)
		{
			int idx = -1;
			for (size_t i = 0; i < s_EventSteppers.size(); i++)
			{
				if (&s_EventSteppers[i] == &eventStep)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			s_EventSteppers.erase(s_EventSteppers.begin() + idx);

		}
		
		void Game::AddEventStepper(f_VoidFunction eventStep)
		{
			s_EventSteppers.push_back(eventStep);
		}

		void Game::RemoveUpdater(f_VoidFunction updater)
		{
			int idx = -1;
			for (size_t i = 0; i < s_Updaters.size(); i++)
			{
				if (&s_EventSteppers[i] == &updater)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)return;

			s_Updaters.erase(s_Updaters.begin() + idx);

		}

		void Game::AddUpdater(f_VoidFunction updater)
		{
			s_EventSteppers.push_back(updater);
		}

		Rect Game::GetGameBounds()
		{
			return Rect(0 + s_Padding, 0 + s_Padding,
				s_Width - ((int)s_Padding * 2.5), s_Height - ((int)s_Padding * 2.5));
		}

		void Game::SetGamePadding(int padding) { s_Padding = padding; }
	}
}