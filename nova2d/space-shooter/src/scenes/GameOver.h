#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"
#include "graphics/Text.h"
#include "input/TextInput.h"
#include <vector>

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
		Text* playerNameLabel = nullptr;
		TextInput* playerNameInput = nullptr;

		std::vector<Text*> highscoresLabels;

	public:

		GameOver(std::string sceneName) : Scene(sceneName) { };
		~GameOver() { };

		void Update() override
		{
			
		}

		void Start() override
		{
			highscoresLabels.clear();

			title = new Text("font1", "Game Over", "red",
				Rect(Game::s_Width / 2 - 250, 32, 500, 60), 0);
			
			auto score = n2dScoreGet();

			playerScore = new Text("font1", "Top Scores", "bright-blue",
				Rect(Game::s_Width / 2 - 150, 332, 300, 30), 0);

			std::vector<HighScore> highscores;
			unsigned long lowestScore;
			int startY = 400;
			int padding = 45;
			n2dSQLScoreTopN(6, highscores, lowestScore);

			int c = 0;
			int cMax = (int)highscores.size();

			if (cMax > 0)
			{
				for (size_t i = 0; i < 3; i++)
				{
					for (int j = -1; j < 2; j+=2)
					{
						if (c >= cMax) break;

						HighScore h = highscores[c];
					
						int x = j * padding * 4;
						Text* t = new Text("font1", h.PlayerName + "    " + std::to_string(h.PlayerScore), "white",
							Rect(Game::s_Width / 2 - 100 + x, startY + i * padding, 200, 30), 0);
					
						highscoresLabels.push_back(t);
					
						c++;
					}
				
				}
			}

			playerScore = new Text("font1", "Your Score: " + std::to_string(score), "white",
				Rect(Game::s_Width / 2 - 150, 148, 300, 45), 0);

			if (score > 0)
			{
				playerNameLabel = new Text("font1", "enter alias:", "light-blue",
					Rect(Game::s_Width / 2 - 100, 216, 200, 20), 0);

				playerNameInput = new TextInput("font1", "", "white", "dark-blue", 
					Rect(Game::s_Width / 2 - 100, 248, 200, 20), 0);
				playerNameInput->Configure(true, 8);
			}

			spaceToContinue = new Text("font1", "press enter to continue", "yellow",
				Rect(Game::s_Width / 2 - 100, Game::s_Height - 50, 200, 20), 0);


			n2dAddKeyDownListener(SDLK_RETURN, GameOver::OnEnter, this);

		}

		void OnEnter()
		{
			n2dRemoveKeyDownListener(SDLK_RETURN);
			auto score = n2dScoreGet();
			
			if (score > 0)
			{
				std::string playerName = playerNameInput->GetText();
				if (playerName == "") return;

				n2dSQLScoreAdd(playerName, score);
			}

			n2dSceneChange("mainMenu");
		}

		void End() override
		{
			if(title)
				title->DestroySelf();
			
			if(playerScore)
				playerScore->DestroySelf();
			
			if(spaceToContinue)
				spaceToContinue->DestroySelf();
			
			if(playerNameInput)
				playerNameInput->DestroySelf();
			
			if (playerNameLabel)
				playerNameLabel->DestroySelf();

			for (size_t i = 0; i < highscoresLabels.size(); i++)
			{
				if (highscoresLabels[i])
					highscoresLabels[i]->DestroySelf();
			}
		}

	};
}