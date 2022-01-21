#pragma once

#include "ai/SimpleFollower.h"
#include "controllers/SimpleBulletController.h"
#include <string>
#include "components/SimpleStatBar.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::components;

	class Pawn
		: public SimpleFollower
	{

	private:

		float m_DelayShoot = 0.0f;
		float m_DelayShootMin = 1000.0f;
		float m_DelayShootMax = 2000.0f;

		SimpleStatBar* m_HealthBar = nullptr;
		int m_Health = 32;

	public:

		Pawn(std::string assetName, Vec2Int position, Vec2Int size, 
			char layer, Positional* target, const float moveUpdateDelay);
		
		~Pawn();
		
		void ConfigureShoot(float minShootDelayMS, float maxShootDelayMS) { m_DelayShootMin = minShootDelayMS * 2; m_DelayShootMax = maxShootDelayMS * 2; }

		Rect GetAliveBounds() const { return m_AliveBounds; }

		void Update();
		void Shoot();

		void Hurt(int damage);

	};
}