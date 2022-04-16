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
		m_ContactListener = new DemoSceneContactListener();
		EnablePhysics(true, m_ContactListener);
		PhysicsEnableDebug(true);

		n2dAssetsLoadAndAddTexture("ship", "res/lander-TX518.png");
		n2dAssetsLoadAndAddTexture("alien", "res/Ralph-TX18.png");
		n2dAssetsLoadAndAddTexture("planet", "res/planet.png");

		planet = new PhySprite("planet", Vec2(Game::s_Width - 256, Game::s_Height - 256),
			Vec2Int(256, 256), 2);
		planet->ConfigurePhysicsSensorCircle("planet", true, 200);

		player = new PhySprite("ship", Game::GetCenterScreen(), Vec2Int(32, 32),
			10);
		player->ConfigurePhysicsRect("player", false);

		alien = new PhySprite("alien", Vec2(50, 50), Vec2Int(32, 32), 2);
		alien->ConfigurePhysicsRect("alien", false);
		alien->SetScale(2);

	}

	void DemoScene::Update()
	{
		if (n2dIsKeyDown(SDLK_UP))
		{
			if (player)
			{
				player->ApplyForce(100, Directions::Up);
			}
		}

		if (n2dIsKeyDown(SDLK_DOWN))
		{
			if (player)
			{
				player->ApplyForce(100, Directions::Down);
			}
		}

		if (n2dIsKeyDown(SDLK_LEFT))
		{
			if (player)
			{
				player->ApplyForce(100, Directions::Left);
			}
		}

		if (n2dIsKeyDown(SDLK_RIGHT))
		{
			if (player)
			{
				player->ApplyForce(100, Directions::Right);
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