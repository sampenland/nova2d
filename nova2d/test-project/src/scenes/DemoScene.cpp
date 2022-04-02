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
		EnablePhysics(true, Vec2(0, 9.8));
	}

	void DemoScene::Update()
	{

	}

	void DemoScene::End()
	{

	}

	void DemoScene::DestroySelf()
	{

	}
}