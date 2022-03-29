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
		(*x) = 0;
		
		// fails 
		//n2dTweenAdd(true, x, 20, 10.f, 1000, false, false, TweenTypes::EaseInSine);
		
		// fails
		//n2dTweenAdd(true, x, -10, -20.f, 1000, false, false, TweenTypes::EaseInSine);
		
		


		 
		
		
		// works
		//n2dTweenAdd(true, x, 0, 10.f, 1000, false, false, TweenTypes::EaseInSine);
		
		// works
		//n2dTweenAdd(true, x, 10, 0.f, 1000, false, false, TweenTypes::EaseInSine);

		// works
		//n2dTweenAdd(true, x, -10, 10.f, 1000, false, false, TweenTypes::EaseInSine);

		// works
		//n2dTweenAdd(true, x, 10, -20.f, 1000, false, false, TweenTypes::EaseInSine);

		// works
		//n2dTweenAdd(true, x, -20, -10.f, 1000, false, false, TweenTypes::EaseInSine);
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