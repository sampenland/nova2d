#pragma once

#include "ai/SimpleWeakAI.h"
#include "controllers/SimpleBulletController.h"
#include <string>
#include "components/SimpleStatBar.h"
#include "components/HitDisplay.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::components;

	class Pawn
		: public SimpleWeakAI
	{

	private:

		SimpleStatBar* m_HealthBar = nullptr;
		int m_Health = 8;

	public:

		bool m_Dead = 0;

	public:

		Pawn(const std::string& assetName, Vec2 position, Vec2Int size,
			char layer, const float moveUpdateDelay, float shootMin, float shootMax);

		void PawnUpdate();
		void Hurt(int damage);
		void SmallExplosion();
		void DisplayHit(int damage);

		void DestroySelf() override;

	};
}