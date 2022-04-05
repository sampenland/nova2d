#include "Game.h"
#include "../graphics/Renderer.h"
#include "../graphics/AnsiColor.h"
#include "../graphics/DrawLayers.h"

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

		bool Game::s_Debug = true;
		bool Game::s_DebugVerbose = false;

		novazero::graphics::Renderer* Game::s_Renderer;
		ColorManager* Game::s_ColorManager;
		InputHandler* Game::s_InputHandler;
		AssetManager* Game::s_AssetManager;
		SceneManager* Game::s_SceneManager;
		FontManager* Game::s_FontManager;
		SQLManager* Game::s_SQLManager;
		DebugOverlay* Game::s_DebugOverlay;
		Director* Game::s_Director;
		AudioManager* Game::s_AudioManager;

		unsigned int Game::s_IDCount;
		int Game::s_Width;
		int Game::s_Height;
		double Game::s_DeltaTime;
		double Game::s_FPS;
		int Game::s_PaddingT;
		int Game::s_PaddingB;
		int Game::s_PaddingL;
		int Game::s_PaddingR;
		int Game::s_ExitCode = 0;
		bool Game::s_Running = 0;
		unsigned int Game::s_Score = 0;
		float Game::s_TimeScale = 1.0f;
		float Game::s_TimeScaleMemory = 1.0f;
		SDL_KeyCode Game::s_PauseKey = SDLK_p;
		SDL_Haptic* Game::s_Rumbler = nullptr;

		// --------------------------------
		Game::Game(const char* title, const Vec2Int screenSize)
			: m_Title(title), NOW(0), LAST(0)
		{
			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			s_Width = (int)floor(screenSize.x);
			s_Height = (int)floor(screenSize.y);

			if (m_MainWindow)
				s_Running = true;
			else
				return;

			SDL_StartTextInput();

			s_ColorManager = new ColorManager();

			n2dAddColor("white", "ffffff", 255);
			n2dAddColor("black", "1f1f1f", 255);
			n2dAddColor("red", "f02b2b", 255);
			n2dAddColor("green", "2bf038", 255);
			n2dAddColor("yellow", "d8d831", 255);
			n2dAddColor("purple", "252446", 255);
			n2dAddColor("dark-blue", "203562", 255);
			n2dAddColor("blue", "1e579c", 255);
			n2dAddColor("a20-blue", "1e579c", 20);
			n2dAddColor("light-blue", "0098db", 255);
			n2dAddColor("bright-blue", "0ce6f2", 255);
			n2dAddColor("transparent", "000000", 0);

			s_Renderer = new novazero::graphics::Renderer(*(m_MainWindow->GetWindow()), new Color(100,100,100,1));
			n2dBlend(true);

			s_InputHandler = new InputHandler();
			s_AssetManager = new AssetManager();
			s_SceneManager = new SceneManager();
			s_FontManager = new FontManager();
			s_SQLManager = new SQLManager();
			s_Director = new Director();
			s_AudioManager = new AudioManager();

			NOW = SDL_GetPerformanceCounter();
			LAST = 0;

			n2dPauseKeyClear();

			srand((unsigned int)time(NULL));

			if(n2dDebug)
				LOG(LVL_CONFIRMATION, "nova2d [" + std::string(NOVA_VERSION) + "] : Steam Game Engine started. https://n2d.dev");

		}

		Camera* Game::GetCamera()
		{
			return Game::s_Renderer->s_DrawLayers->GetCamera();
		}

		void Game::ConfigureFirstScene(const std::string& sceneName)
		{
			s_SceneManager->ConfigureFirstScene(sceneName);
		}

		void Game::PauseGame(bool pause)
		{
			if (!pause)
			{
				n2dTimeScaleSet(Game::s_TimeScaleMemory);
			}
			else
			{
				Game::s_TimeScaleMemory = n2dTimeScale;
				n2dTimeScaleSet(0.f);
			}
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
		void Game::ConfigureDebugOverlay(bool isVisible)
		{
			if (s_DebugOverlay) s_DebugOverlay->DestroySelf();

			s_DebugOverlay = new DebugOverlay(Vec2Int(32, 48));
			
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

				if (Game::s_Debug && (event.key.keysym.sym == SDLK_BACKQUOTE)) // ` key press
				{
					s_Director->Toggle();
				}

				if (event.key.keysym.sym == Game::s_PauseKey)
				{
					n2dPauseGame(n2dTimeScale != 0.f);
				}

				break;

			case SDL_JOYAXISMOTION:

				s_InputHandler->JoyAxisChange(&event);
				
				break;

			case SDL_JOYHATMOTION:

				s_InputHandler->JoyHatChange(&event);

				break;

			case SDL_JOYBUTTONDOWN:

				if (Game::IsDebug() && event.jbutton.button == SDL_CONTROLLER_BUTTON_GUIDE + 1)
				{
					s_Director->Toggle();
				}

				if (event.jbutton.button == SDL_CONTROLLER_BUTTON_START + 1)
				{
					n2dPauseGame(n2dTimeScale != 0.f);
				}

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
			Game::s_DeltaTime = (double)(n2dTimeScale * ((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency()));
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

		float Game::GetDeltaTime() 
		{ 
			return (float)s_DeltaTime / 100.f; 
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
			{
				m_SceneManager->DestroySelf();
				delete m_SceneManager;
			}

			if (m_MainWindow)
			{
				m_MainWindow->DestroySelf();
				delete m_MainWindow;
			}

			if (s_Renderer)
			{
				s_Renderer->DestroySelf();
				delete s_Renderer;
			}

			if (s_ColorManager)
			{
				s_ColorManager->DestroySelf();
				delete s_ColorManager;
			}

			if (s_InputHandler)
			{
				s_InputHandler->DestroySelf();
				delete s_InputHandler;
			}

			if (s_AssetManager)
			{
				s_AssetManager->DestroySelf();
				delete s_AssetManager;
			}

			if (s_AudioManager)
			{
				s_AudioManager->DestroySelf();
				delete s_AudioManager;
			}

			if (s_ExitCode == 0)
			{
				if(n2dDebug)
					LOG(LVL_CONFIRMATION, "nova2d [" + std::string(NOVA_VERSION) + "] : Steam Game Engine ended successfully.");
			}
			else
			{
				if(n2dDebug)
					LOG(LVL_FATAL_ERROR, "nova2d [" + std::string(NOVA_VERSION) + "] : Steam Game Engine FAILED WITH EXIT CODE: " + tostring(s_ExitCode));
			}

			SDL_Quit();

		}

		Rect Game::GetGameBounds(float paddingOverride)
		{
			Rect bounds = Rect(
				s_PaddingL * CAMERA_ZOOM,
				s_PaddingT * CAMERA_ZOOM,
				(s_Width - s_PaddingR) * CAMERA_ZOOM,
				(s_Height - s_PaddingB) * CAMERA_ZOOM
			);

			bounds.x -= paddingOverride;
			bounds.y -= paddingOverride;
			bounds.w += paddingOverride;
			bounds.h += paddingOverride;

			return bounds;
		}

		void Game::SetGamePadding(float padding) 
		{ 
			s_PaddingT = (int)padding; 
			s_PaddingB = (int)padding; 
			s_PaddingL = (int)padding; 
			s_PaddingR = (int)padding; 
		}

		void Game::SetGamePadding(float paddingTop, float paddingBottom, float paddingLeft, float paddingRight)
		{
			s_PaddingT = (int)paddingTop;
			s_PaddingB = (int)paddingBottom;
			s_PaddingL = (int)paddingLeft;
			s_PaddingR = (int)paddingRight;
		}
	}
}