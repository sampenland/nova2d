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

		std::string m_PlayerNumber = "player1";

		bool m_CanSpace = true;
		float m_SpaceDelayReset = 0.0f;
		double m_SpaceDelay = 0.00;

		Timer* m_ShootTimer = nullptr;

		int m_Lives = 20;
		std::vector<Sprite*> m_LifeSprites;

		unsigned int m_CleanID = 0;

	public:

		Player(std::string assetName, std::string playerNumber, Vec2 position, Vec2Int size, char layer);
		~Player();

		Sprite* GetSprite() const { return m_Sprite; }

		void Configure(float spaceDelayReset) { m_SpaceDelayReset = spaceDelayReset / 10; }

		void OnCollision(Collision* collision) override;

		void Update();
		void OnSpace();
		void Shoot();

		void SmallExplosion();
		void Quit();

	public:

		static const Uint32 s_StreakTime = 1250;
		static Uint32 s_LastPawnKillTime;
		static int s_Streak;
		static int s_MaxStreak;

		void NewKill()
		{
			Uint32 ticks = SDL_GetTicks();
			Uint32 deltaTicks = ticks - s_LastPawnKillTime;
			LOG(LVL_WARNING, std::to_string(deltaTicks) + " :: " + std::to_string(s_StreakTime));
			if (deltaTicks < s_StreakTime)
			{
				s_Streak++;
				if (s_Streak > s_MaxStreak)s_MaxStreak = s_Streak;
			}
			else
			{
				s_Streak = 0;
			}
			s_LastPawnKillTime = ticks;
		}

	};
}