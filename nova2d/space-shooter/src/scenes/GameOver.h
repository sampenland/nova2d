#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::input;

	class GameOver :
		public Scene
	{

	private:

		Sprite* title = nullptr;

	public:

		GameOver(std::string sceneName) : Scene(sceneName) { };
		~GameOver() { };

		void Update() override
		{
			
		}

		void Start() override
		{
			title = new Sprite("gameOverTitle", Vec2Int(Game::s_Width / 2, Game::s_Height / 8),
				Vec2Int(256, 128), 0);

			title->SetPosition(Vec2Int(title->GetX() - title->GetWidth() / 2, title->GetY()));

			n2dAddKeyDownListener(SDLK_SPACE, GameOver::OnSpace, this);

		}

		void OnSpace()
		{
			n2dSceneChange("mainMenu");
		}

		void End() override
		{
			delete title;
		}

	};
}