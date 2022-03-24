#pragma once
#include "core/Scene.h"
#include "SampleScene.h"
#include "core/Game.h"

namespace emptyproject
{
	using namespace novazero::core;

	SampleScene::SampleScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void SampleScene::Start()
	{
		const int textWidth = 500;
		m_NovaTitle = new Text("font1", "Thanks for using nova2d", "white",
			Rect(Game::s_Width / 2 - textWidth / 2, Game::s_Height / 2 - 75 / 2, textWidth, 75), 0);
	}

	void SampleScene::Update()
	{
		
	}

	void SampleScene::End()
	{

	}

	void SampleScene::DestroySelf()
	{

	}
}