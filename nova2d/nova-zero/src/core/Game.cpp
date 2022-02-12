#include "Game.h"
#include "../graphics/Renderer.h"
#include "../graphics/AnsiColor.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;
		using namespace utils;
		using namespace physics;
		using namespace input;
		using namespace debug;

		bool Game::s_Debug = false;

		novazero::graphics::Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;
		InputHandler* Game::s_InputHandler;
		AssetManager* Game::s_AssetManager;
		SceneManager* Game::s_SceneManager;
		FontManager* Game::s_FontManager;
		SQLManager* Game::s_SQLManager;
		DebugOverlay* Game::s_DebugOverlay;

		unsigned int Game::s_IDCount;
		int Game::s_Width;
		int Game::s_Height;
		double Game::s_DeltaTime;
		double Game::s_FPS;
		int Game::s_Padding;
		int Game::s_ExitCode = 0;
		bool Game::s_Running = 0;
		unsigned int Game::s_Score = 0;
		float Game::s_TimeScale = 1.0f;

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

			SDL_StartTextInput();

			s_ColorManager = new ColorManager();

			n2dAddColor("white", "ffffff", 255);
			n2dAddColor("black", "000000", 255);
			n2dAddColor("red", "f02b2b", 255);
			n2dAddColor("green", "2bf038", 255);
			n2dAddColor("yellow", "d8d831", 255);

			s_Renderer = new novazero::graphics::Renderer(*(m_MainWindow->GetWindow()), new Color(100,100,100,1));
			s_InputHandler = new InputHandler();
			s_AssetManager = new AssetManager();
			s_SceneManager = new SceneManager();
			s_FontManager = new FontManager();
			s_SQLManager = new SQLManager();

			s_Width = (int)floor(screenSize.x);
			s_Height = (int)floor(screenSize.y);

			NOW = SDL_GetPerformanceCounter();
			LAST = 0;

			srand((unsigned int)time(NULL));

			LOG(LVL_CONFIRMATION, "Nova Boot : Game Engine started.");

		}

		void Game::ConfigureFirstScene(const std::string& sceneName)
		{
			s_SceneManager->ConfigureFirstScene(sceneName);
		}

		void Game::ConfigureSQL(const std::string& databaseName, const std::string& connectionString, const std::string& user, 
			const std::string& pass, bool useNovaSQLScoring)
		{
			s_SQLManager->Configure(databaseName, connectionString, user, pass);

			if (useNovaSQLScoring)
			{
				n2dSQLScoreTableCreation(12, 10);
			}
		}

		// Must be called before debug position setting
		void Game::ConfigureDebug(bool isVisible)
		{
			if (s_DebugOverlay) s_DebugOverlay->DestroySelf();

			s_DebugOverlay = new DebugOverlay(Vec2Int(32, 32));
			
			if (isVisible)
			{
				s_DebugOverlay->Show();
			}
			else
			{
				s_DebugOverlay->Hide();
			}
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

			case SDL_TEXTINPUT:
				s_InputHandler->OnTextChange(&event);
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
			
			if (frameTime > 0)
				Game::s_FPS = 1000.0 / (double)frameTime;

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
			s_SceneManager->Clean();
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

		Rect Game::GetGameBounds(float paddingOverride)
		{
			if (paddingOverride != 0)
			{
				return Rect(-paddingOverride, -paddingOverride, s_Width + paddingOverride, s_Height + paddingOverride);
			}

			return Rect(0.f + s_Padding, 0.f + s_Padding,
				s_Width - ((s_Padding * 2.5f)), s_Height - ((s_Padding * 2.5f)));
		}

		void Game::SetGamePadding(float padding) { s_Padding = (int)padding; }
	}
}