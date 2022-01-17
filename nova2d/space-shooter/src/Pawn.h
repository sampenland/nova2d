#pragma once

#include "ai/SimpleFollower.h"
#include "controllers/SimpleBulletController.h"
#include <string>

namespace spaceshooter
{
	using namespace novazero::ai;

	class Pawn
		: public SimpleFollower
	{

	private:

		float m_DelayShoot = 0.0f;
		float m_DelayShootReset = 1.0f;

	public:

		Pawn(std::string assetName, Vec2Int position, Vec2Int size, 
			char layer, Positional* target, const float moveUpdateDelay);
		
		~Pawn();
		
		void ConfigureShoot(float maxShootDelay) { m_DelayShootReset = maxShootDelay; }

		Rect GetAliveBounds() const { return m_AliveBounds; }

		void Update();
		void Shoot();

	};
}