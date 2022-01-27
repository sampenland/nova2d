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

		bool m_CanSpace = true;
		float m_SpaceDelayReset = 0.0f;
		double m_SpaceDelay = 0.00;

		Timer* m_ShootTimer = nullptr;

		int m_Lives = 3;
		std::vector<Sprite*> m_LifeSprites;

		unsigned int m_CleanID = 0;

	public:

		Player(std::string assetName, Vec2Int position, Vec2Int size, char layer);
		~Player();

		Sprite* GetSprite() const { return m_Sprite; }

		void Configure(float spaceDelayReset) { m_SpaceDelayReset = spaceDelayReset / 10; }

		void OnCollision(Collision* collision) override;

		void Update();
		void OnSpace();
		void Shoot();

		void SmallExplosion();
		void Quit();

	};
}