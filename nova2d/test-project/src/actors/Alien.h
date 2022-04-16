#pragma once
#include "physics/PhySprite.h"
#include "physics/ai/PhySimpleWeakAI.h"

namespace testproject
{
	using namespace novazero::physics;
	using namespace novazero::physics::ai;
	using namespace novazero::ai;

	class Alien : 
		public PhySimpleWeakAI
	{

	private:

		Timer* m_Shooter = nullptr;
		Timer* m_Mover = nullptr;

	public:

		Alien(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

		void Shoot();
		void TryMove();

		void DestroySelf();
	};
}