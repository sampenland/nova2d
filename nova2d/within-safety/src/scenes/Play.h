#pragma once
#include "core/Scene.h"
#include "physics/Physics.h"

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

	public:

		Play(const std::string& sceneName);

		void Start();
		void End();
		void Update();

		void ForceControl();
		void ShootControl();
		
	};
}