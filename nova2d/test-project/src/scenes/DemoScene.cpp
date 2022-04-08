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
		player->ConfigurePhysicsRect(false);
	}

	void DemoScene::Update()
	{
		if (n2dIsKeyDown(SDLK_UP))
		{
			if (player)
			{
				player->ApplyForce(Vec2(100, 100));
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