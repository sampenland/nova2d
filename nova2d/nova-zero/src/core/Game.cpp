#include "Game.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace core
	{
		using namespace maths;

		Game::Game(const maths::vec2 screenSize, const char* title)
			: m_Width((int)floor(screenSize.x)), m_Height((int)floor(screenSize.y)), 
			m_Title(title)
		{

			m_SceneManager = new SceneManager();
			m_MainWindow = new Window(screenSize, title);

			if (m_MainWindow)
				m_Running = true;
			else
				return;

		}

		void Game::Update()
		{
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

		}
	}
}