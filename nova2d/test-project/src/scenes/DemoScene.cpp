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
		float* x = new float;
		(*x) = -608;
		n2dTweenAdd(true, x, -608.f, -508.f, 1000, false, false, TweenTypes::EaseInExpo);

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