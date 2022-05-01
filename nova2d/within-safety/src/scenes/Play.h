#pragma once
#include "core/Scene.h"
#include "physics/Physics.h"
#include "core/Timer.h"

namespace withinsafety
{
	using namespace novazero::core;
	using namespace novazero::physics;
	using namespace novazero::physics::ai;

	class Play :
		public Scene
	{

	private:

		PhySensor* m_Planet = nullptr;
		PhySprite* m_Player = nullptr;

		const float SHOOT_RESET = 20.f;
		float m_ShootReady = -1.f;

		Timer* m_Enemy1Creator = nullptr;

	public:

		Play(const std::string& sceneName);

		void Start();
		void End();
		void Update();

		void CreateEnemy1();

		void ForceControl();
		void ShootControl();
		
	};
}