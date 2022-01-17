#pragma once
#include "ai/SimpleWeakAI.h"
#include "ai/SimpleFollower.h"
#include "Pawn.h"
#include "core/Common.h"
#include <vector>
#include "Player.h"

namespace spaceshooter
{
	using namespace novazero::ai;
	using namespace novazero::controllers;
	using namespace novazero::core;

	class Leader
		: public SimpleWeakAI
	{
		
	private:

		std::vector<Pawn*> m_Pawns;
		float m_DelayShoot = 0.0f;
		float m_DelayShootMin = 1.0f;
		float m_DelayShootMax = 5.0f;

	public:

		Leader(std::string assetName, Vec2Int position, Vec2Int size, char layer);
		~Leader();

		void ConfigureShoot(float minShootDelay, float maxShootDelay) { m_DelayShootMin = minShootDelay * 2; m_DelayShootMax = maxShootDelay * 2; }

		void ShootUpdate();
		void Shoot();

		void DestroySelf() override;

	};
}