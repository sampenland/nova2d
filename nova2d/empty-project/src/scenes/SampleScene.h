#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"

namespace emptyproject
{
	using namespace novazero::core;
	using namespace novazero::graphics;

	class SampleScene :
		public Scene
	{

	private:

		Text* title = nullptr;

	public:

		SampleScene(const std::string& sceneName)
			: Scene(sceneName)
		{
		};

		void Update() override
		{
		}

		void Start() override
		{
			title = new Text("font1", "nova 2D", "white", Rect(0, 0, 200, 100), 0);
			title->SetPosition(Vec2(Game::GetCenterScreen().x - 100.f, Game::GetCenterScreen().y - 50.f));
		}

		void OnEscape()
		{
			End();
			Game::EndGame(0);
		}

		void End() override
		{
			
		}

	};
}