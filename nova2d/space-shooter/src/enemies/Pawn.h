#pragma once

#include "ai/SimpleWeakAI.h"
#include "controllers/SimpleBulletController.h"
#include <string>
#include "components/SimpleStatBar.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::components;

	class Pawn
		: public SimpleWeakAI
	{

	private:

		float m_DelayShoot = 0.0f;
		float m_DelayShootMin = 1000.0f;
		float m_DelayShootMax = 2000.0f;

		SimpleStatBar* m_HealthBar = nullptr;
		int m_Health = 8;
		std::string m_KilledBy = "player0";

	public:

		bool m_Dead = 0;

	public:

		Pawn(std::string assetName, Vec2 position, Vec2Int size, 
			char layer, const float moveUpdateDelay, float shootMin, float shootMax);
		
		void ConfigureShoot(float minShootDelayMS, float maxShootDelayMS) { m_DelayShootMin = minShootDelayMS * 2; m_DelayShootMax = maxShootDelayMS * 2; }

		Rect GetAliveBounds() const { return m_AliveBounds; }

		void PawnUpdate();
		void Shoot();

		void Hurt(int damage, std::string damager);
		void SmallExplosion();

		void DestroySelf() override;

	};
}