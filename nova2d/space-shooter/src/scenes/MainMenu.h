#include "core/Scene.h"
#include "maths/Vec2Int.h"
#include "core/EventListener.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::input;
	using namespace novazero::graphics;

	class MainMenu :
		public Scene
	{

	private:

		Text* title = nullptr;
		Text* spaceToContinue = nullptr;

	public:

		MainMenu(std::string sceneName)
			: Scene(sceneName)
		{

		};

		~MainMenu() { };

		void Update() override
		{

		}

		void Start() override
		{
			n2dScoreSet(0);

			title = new Text("font1", "SPACE SHOOTER", "white",
				Rect(Game::s_Width / 2 - 200, Game::s_Height / 4, 400, 40), 0);

			spaceToContinue = new Text("font1", "press space to continue", "yellow",
				Rect(Game::s_Width / 2 - 100, Game::s_Height / 2 + 50, 200, 20), 0);
		
			auto startListening = new auto([=] {
				StartListening();
			});

			Timer* t = new Timer(1000, false, *startListening);
		}

		void StartListening()
		{
			n2dAddKeyDownListener(SDLK_SPACE, MainMenu::OnSpace, this);
			n2dAddKeyDownListener(SDLK_ESCAPE, MainMenu::OnEscape, this);
		}

		void OnSpace()
		{
			n2dRemoveKeyDownListener(SDLK_SPACE);
			n2dRemoveKeyDownListener(SDLK_ESCAPE);
			n2dSceneChange("level1");
		}

		void OnEscape()
		{
			Game::EndGame(0);
		}

		void End() override
		{
			delete title;
			delete spaceToContinue;
		}

	};
}