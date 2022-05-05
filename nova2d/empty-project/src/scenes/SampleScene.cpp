#pragma once
#include "core/Scene.h"
#include "SampleScene.h"
#include "core/Game.h"
#include "physics/PhySprite.h"
#include "physics/PhySensor.h"
#include "particles/ParticleSystem.h"
#include "controllers/BasicController.h"

namespace emptyproject
{
	using namespace novazero::core;
	using namespace novazero::physics;
	using namespace novazero::particles;
	using namespace novazero::controllers;

	SampleScene::SampleScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void SampleScene::Start()
	{
		/*const int textWidth = 500;
		m_NovaTitle = new Text("font1", "Thanks for using nova2d", "white",
			Rect(Game::s_Width / 2 - textWidth / 2, Game::s_Height / 2 - 75 / 2, textWidth, 75), 0);*/

		EnablePhysics(true, Vec2(0, 0), 0.f);
		PhysicsEnableDebug(true);
		n2dAssetsLoadAndAddTexture("bullet", "res/bullet.png");

		BasicController* bs = new BasicController("bullet", "collider", Game::GetCenterScreen(), Vec2(32, 32),
			Vec2Int(32, 32), 10);
		bs->ConfigurePhysicsCircle(false, 20);
		bs->EnableArrowKeys(true);
		bs->ConfigureMoveSpeed(5);
		
		/*Vec2 a = Vec2(800, 150);
		Vec2 b = Vec2(Game::s_Width / 2, Game::s_Height / 2);

		Text* t1 = new Text("font1", "A", "white", Rect(a.x, a.y, 10.f, 10.f), 10);
		Text* t2 = new Text("font1", "B", "white", Rect(b.x, b.y, 10.f, 10.f), 10);


		PhySprite* s = new PhySprite("bullet", a, Vec2(32, 32), 20, Vec2Int(32, 32), "collider");
		s->ConfigurePhysicsRect(false);
		
		Vec2 dir = Vec2::LookAtVec(a, b).normalize();
		s->ApplyForce(dir, 10.f);*/

		//ParticleSystem* p = n2dAddParticleSystem("bullet", Vec2Int(32, 32), "ps", 100, 5, 10);
		//p->SetLifetime(2, 5);
		//
		//Timer* t = new Timer(2000, true, [=]() {
		//	p->BurstParticles(50, Game::GetCenterScreen(), 300, false);
		//});
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