#include "Game.h"
#include "../graphics/Renderer.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;
		using namespace utils;
		using namespace physics;
		using namespace input;

		novazero::graphics::Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;
		InputHandler* Game::s_InputHandler;
		AssetManager* Game::s_AssetManager;
		SceneManager* Game::s_SceneManager;
		FontManager* Game::s_FontManager;

		unsigned int Game::s_IDCount;
		int Game::s_Width;
		int Game::s_Height;
		double Game::s_DeltaTime;
		int Game::s_Padding;
		int Game::s_ExitCode = 0;
		bool Game::s_Running = 0;
		unsigned int Game::s_Score = 0;

		// --------------------------------
		Game::Game(const Vec2Int screenSize, const char* title)
			: m_Title(title), NOW(0), LAST(0)
		{

			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			if (m_MainWindow)
				s_Running = true;
			else
				return;

			s_ColorManager = new ColorManager();
			s_Renderer = new novazero::graphics::Renderer(*(m_MainWindow->GetWindow()), new Color(100,100,100,1));
			s_InputHandler = new InputHandler();
			s_AssetManager = new AssetManager();
			s_SceneManager = new SceneManager();
			s_FontManager = new FontManager();

			s_Width = (int)floor(screenSize.x);
			s_Height = (int)floor(screenSize.y);

			NOW = SDL_GetPerformanceCounter();
			LAST = 0;

		}

		void Game::ConfigureFirstScene(std::string sceneName)
		{
			s_SceneManager->ConfigureFirstScene(sceneName);
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
				s_Running = false;
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
			s_SceneManager->Update();
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

			SDL_Quit();

		}

		Rect Game::GetGameBounds()
		{
			return Rect(0 + s_Padding, 0 + s_Padding,
				s_Width - ((int)(s_Padding * 2.5)), s_Height - ((int)(s_Padding * 2.5)));
		}

		void Game::SetGamePadding(int padding) { s_Padding = padding; }
	}
}