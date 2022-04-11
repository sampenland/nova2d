#include "DemoScene.h"
#include "logging/logging.h"
#include "core/Game.h"

namespace testproject
{
	DemoScene::DemoScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void DemoScene::Start()
	{
		EnablePhysics(true);
		PhysicsEnableDebug(true);

		n2dAssetsLoadAndAddTexture("ship", "res/ship.png");
		player = new PhySprite("ship", Game::GetCenterScreen(), Vec2Int(16, 16),
			10);

		std::vector<Vec2> triangle;
		triangle.push_back(Vec2(8, 0));
		triangle.push_back(Vec2(0, 16));
		triangle.push_back(Vec2(16, 16));
		player->ConfigurePhysicsPolygon(false, triangle, 3);
	}

	void DemoScene::Update()
	{
		if (n2dIsKeyDown(SDLK_UP))
		{
			if (player)
			{
				player->ApplyForce(-100);
			}
		}

		if (n2dIsKeyDown(SDLK_DOWN))
		{
			if (player)
			{
				player->ApplyForce(100);
			}
		}

		if (n2dIsKeyDown(SDLK_LEFT))
		{
			if (player)
			{
				player->ApplyAngularForce(-10);
			}
		}

		if (n2dIsKeyDown(SDLK_RIGHT))
		{
			if (player)
			{
				player->ApplyAngularForce(10);
			}
		}
	}

	void DemoScene::End()
	{

	}

	void DemoScene::DestroySelf()
	{

	}
}