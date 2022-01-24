#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::input;

	class GameOver :
		public Scene
	{

	private:

		Text* title = nullptr;
		Text* playerScore = nullptr;
		Text* spaceToContinue = nullptr;


	public:

		GameOver(std::string sceneName) : Scene(sceneName) { };
		~GameOver() { };

		void Update() override
		{
			
		}

		void Start() override
		{
			auto score = n2dScoreGet();

			title = new Text("font1", "Game Over", "red",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 4, 400, 40), 0);

			playerScore = new Text("font1", "Your Score: " + std::to_string(score), "white",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2, 200, 20), 0);

			spaceToContinue = new Text("font1", "press space to continue", "yellow",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2 + 50, 200, 20), 0);

			n2dAddKeyDownListener(SDLK_SPACE, GameOver::OnSpace, this);

		}

		void OnSpace()
		{
			n2dSceneChange("mainMenu");
		}

		void End() override
		{
			delete title;
			delete playerScore;
			delete spaceToContinue;
		}

	};
}