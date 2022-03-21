#include "core/Scene.h"
#include "graphics/Text.h"
#include "core/Timer.h"

namespace emptyproject
{

	using namespace novazero::core;
	using namespace novazero::graphics;

	class MainMenu : public Scene
	{

	private:

		Text* m_Title = nullptr;

	public:

		MainMenu(const std::string& sceneName)
			: Scene(sceneName)
		{
			
		}

		void Start() override
		{
			m_Title = new Text("font1", "Title", "white",
				Rect(100, 100, 100, 50), 0);

			Timer* timer = new Timer(1000, false, n2dMakeFunc(MainMenu::GotoLevel1, this));
		}

		void GotoLevel1()
		{
			n2dSceneChange("level1");
		}

		void Update() override
		{

		}

		void End() override
		{

		}

		void DestroySelf()
		{
			m_Title->DestroySelf();
		}


	};

}