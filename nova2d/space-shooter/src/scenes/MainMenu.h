#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::input;

	class MainMenu :
		public Scene, public EventListener
	{

	private:

		Sprite* title = nullptr;

	public:

		MainMenu() { };
		~MainMenu() { };

		void Update() override
		{

		}

		void Start() override
		{
			title = new Sprite("title", Vec2Int(Game::s_Width / 2, Game::s_Height / 2),
				Vec2Int(256, 128), 0);

			title->SetPosition(Vec2Int(title->GetX() - title->GetWidth() / 2, title->GetY() - title->GetHeight() / 2));
		
			AddKeysEventListener(SDLK_SPACE, &InputHandler::IsKeyDown, std::bind(&MainMenu::OnSpace, this));

		}

		void OnSpace()
		{
			Game::s_SceneManager->ChangeScene("level1");
		}

		void End() override
		{
			delete title;
		}

	};
}