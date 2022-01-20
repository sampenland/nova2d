#include "core/Scene.h"
#include "maths/Vec2Int.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class MainMenu :
		public Scene
	{

	private:

		Sprite* title = nullptr;

	public:

		MainMenu() { Start();  };
		~MainMenu() { };

		void Update() override
		{

		}

		void Start() override
		{
			title = new Sprite("title", Vec2Int(Game::s_Width / 2, Game::s_Height / 2),
				Vec2Int(128, 32), 0);
		}

		void OnSpace()
		{
			
		}

		void End() override
		{
			delete title;
		}

	};
}