#pragma once
#include "core/Scene.h"
#include "SampleScene.h"
#include "core/Game.h"
#include "ai/SimpleWeakAI.h"

namespace emptyproject
{
	using namespace novazero::core;
	using namespace novazero::physics;
	using namespace novazero::ai;

	SampleScene::SampleScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void SampleScene::Start()
	{
		/*const int textWidth = 500;
		m_NovaTitle = new Text("font1", "Thanks for using nova2d", "white",
			Rect(Game::s_Width / 2 - textWidth / 2, Game::s_Height / 2 - 75 / 2, textWidth, 75), 0);*/

		Vec2 a = Vec2(800, 150);
		Vec2 b = Vec2(Game::s_Width / 2, Game::s_Height / 2);

		Text* t1 = new Text("font1", "A", "white", Rect(a.x, a.y, 10.f, 10.f), 10);
		Text* t2 = new Text("font1", "B", "white", Rect(b.x, b.y, 10.f, 10.f), 10);

		n2dAssetsLoadAndAddTexture("bullet", "res/bullet.png");

		SimpleWeakAI* sd = new SimpleWeakAI();
		sd->Configure(0.2f, false);
		sd->AddSprite("bullet", a, Vec2Int(32, 32), 20);
		sd->AddPatrolPointLinearMovement(b);

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