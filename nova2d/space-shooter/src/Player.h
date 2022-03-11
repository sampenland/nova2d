#pragma once
#include "components/SimpleStatBar.h"
#include "controllers/UDRLController.h"
#include "maths/Vec2Int.h"
#include "controllers/SimpleBulletController.h"
#include "physics/Collider.h"

namespace spaceshooter
{
	using namespace novazero::graphics;
	using namespace novazero::controllers;
	using namespace novazero::components;

	class Player 
		: public UDRLController, public Referenceable, 
		public Collider
	{

	private:

		const float SHOOT_TIME = 150.f;
		const int FUEL_RIGHT_PADDING = 72;

		bool m_SpacePressed = false;
		float m_SpaceDuration = 0.0f;
		const int c_MaxSpaceHoldTime = 4000;

		Timer* m_ShootTimer = nullptr;

		int m_Lives = 4;
		std::vector<Sprite*> m_LifeSprites;
		Sprite* m_StreakSprite;
		
		float m_Fuel = 100.f;
		SimpleStatBar* m_FuelDisplay = nullptr;
		SimpleStatBar* m_FuelDisplayMain = nullptr;
		Sprite* m_FuelTank = nullptr;

		unsigned int m_CleanID = 0;

		// Damages
		int m_ShootDamage = 2;

	public:

		Player(const std::string& assetName, const std::string& playerNumber, Vec2 position, Vec2Int size, char layer);
		~Player();

		//Sprite* GetSprite() const { return m_Sprite; }

		void OnCollision(Collision* collision) override;

		void Update();
		void OnSpace();
		void OnSpaceUp();
		void Shoot();

		float GetFuel()
		{
			return m_Fuel;
		}

		void DisplayHit(int score, Vec2 pos, const std::string& fontColor);
		void Die();

		void SmallExplosion(Vec2 posIfNotPlayer = Vec2(-100, -100));
		void Quit();

	public:

		static const Uint32 s_StreakTime = 1250;
		
		static Uint32 s_Player1LastPawnKillTime;
		
		static int s_Player1Streak;
		static int s_Player1MaxStreak;

		static void NewKill()
		{
			Uint32 ticks = SDL_GetTicks();
			Uint32 deltaTicks = ticks - s_Player1LastPawnKillTime;
			if (deltaTicks < s_StreakTime)
			{
				s_Player1Streak++;
				if (s_Player1Streak > s_Player1MaxStreak)
					s_Player1MaxStreak = s_Player1Streak;
			}
			else
			{
				s_Player1Streak = 0;
			}
			s_Player1LastPawnKillTime = ticks;
		}

	};
}