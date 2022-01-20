#pragma once

#include "controllers/UDRLController.h"
#include "maths/Vec2Int.h"
#include "controllers/SimpleBulletController.h"
#include "physics/Collider.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;

	class Player 
		: public UDRLController, public Referenceable, 
		public Collider
	{

	private:

		bool m_CanShoot = true;
		float m_ShootDelayReset = 0.0f;
		double m_ShootDelay = 0.00;

		int m_Lives = 3;
		std::vector<Sprite*> m_LifeSprites;

	public:

		Player(std::string assetName, Vec2Int position, Vec2Int size, char layer);
		~Player();

		Sprite* GetSprite() const { return m_Sprite; }

		void Configure(float shootDelayReset) { m_ShootDelayReset = shootDelayReset / 10; }

		void OnCollision(Collision* collision) override;

		void Update();
		void Shoot();

	};
}