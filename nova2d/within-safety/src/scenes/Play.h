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

	public:

		Play(const std::string& sceneName);

		void Start();
		void End();
		void Update();
		
	};
}