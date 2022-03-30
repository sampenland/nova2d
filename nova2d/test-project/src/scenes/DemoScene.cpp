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


		// neg to neg works
		n2dTweenAdd(true, x, -50, -20.f, 1000, false, false, TweenTypes::EaseInSine);
		//n2dTweenAdd(true, x, -20, -50.f, 1000, false, false, TweenTypes::EaseInSine);

		// zero to pos works
		//n2dTweenAdd(true, x, 0, 10.f, 1000, false, false, TweenTypes::EaseInSine);
		// zere to neg works
		//n2dTweenAdd(true, x, 0, -20.f, 1000, false, false, TweenTypes::EaseInSine);
		
		// neg to zero works
		//n2dTweenAdd(true, x, -20, 0.f, 1000, false, false, TweenTypes::EaseInSine);
		// pos to zero works
		//n2dTweenAdd(true, x, 20, 0.f, 1000, false, false, TweenTypes::EaseInSine);
		
		// pos to pos inc and dec works
		//n2dTweenAdd(true, x, 10, 50.f, 1000, false, false, TweenTypes::EaseInSine);
		//n2dTweenAdd(true, x, 50, 10.f, 1000, false, false, TweenTypes::EaseInSine);
		
		// neg to pos works
		//n2dTweenAdd(true, x, -50, 10.f, 1000, false, false, TweenTypes::EaseInSine);
		// pos to neg works
		//n2dTweenAdd(true, x, 30, -10.f, 1000, false, false, TweenTypes::EaseInSine);


		 
		
		
		

		// works
		//n2dTweenAdd(true, x, -10, 10.f, 1000, false, false, TweenTypes::EaseInSine);

		// works
		//n2dTweenAdd(true, x, 10, -20.f, 1000, false, false, TweenTypes::EaseInSine);

		// works
		//n2dTweenAdd(true, x, -20, -10.f, 1000, false, false, TweenTypes::EaseInSine);


		//TODO ------- add n2dDelta into these tweens
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