#pragma once
#include "physics/PhySprite.h"
#include "physics/ai/PhySimpleWeakAI.h"
#include "maths/Maths.h"
#include "MiniAlien.h"

namespace testproject
{
	using namespace novazero::physics;
	using namespace novazero::physics::ai;
	using namespace novazero::ai;
	using namespace novazero::maths;

	class Alien : 
		public PhySimpleWeakAI
	{

	private:

		Timer* m_Shooter = nullptr;
		Timer* m_Mover = nullptr;

		std::vector<MiniAlien*> m_MiniAliens;

	public:

		Alien(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

		void Shoot();
		void TryMove();

		void CreateMiniAlien(int count);

		void DestroySelf();
	};
}