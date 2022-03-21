#include "core/Scene.h"
#include "graphics/Text.h"

namespace emptyproject
{

	using namespace novazero::core;
	using namespace novazero::graphics;

	class Level1 : public Scene
	{

	private:

		Text* m_Title = nullptr;

	public:

		Level1(const std::string& sceneName)
			: Scene(sceneName)
		{

		}

		void Start() override
		{
			m_Title = new Text("font1", "Level 1", "white",
				Rect(300, 300, 100, 50), 0);
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