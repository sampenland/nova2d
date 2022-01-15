#pragma once

#include "controllers/UDRLController.h"
#include "maths/Vec2Int.h"
#include "controllers/SimpleBulletController.h"

#include "SDL.h"

namespace spaceshooter
{
	using namespace novazero;
	using namespace maths;
	using namespace controllers;

	class Player 
		: public UDRLController
	{

	private:

		bool m_CanShoot = true;
		float m_ShootDelayReset = 0.0f;
		float m_ShootDelay = 0.0f;

	public:

		Player(std::string assetName, Vec2Int position, Vec2Int size, char layer);
		~Player();

		void Configure(float shootDelayReset) { m_ShootDelayReset = shootDelayReset / 10; }

		void Update();
		void Shoot();

	};
}