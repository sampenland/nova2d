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

		bool m_SpacePressed = false;
		float m_SpaceDuration = 0.0f;
		const int c_MaxSpaceHoldTime = 4000;

		Timer* m_ShootTimer = nullptr;

		int m_Lives = 20;
		std::vector<Sprite*> m_LifeSprites;
		Sprite* m_StreakSprite;
		DrawCircle* m_ClockPower = nullptr;

		unsigned int m_CleanID = 0;

	public:

		Player(std::string assetName, std::string playerNumber, Vec2 position, Vec2Int size, char layer);
		~Player();

		Sprite* GetSprite() const { return m_Sprite; }

		void OnCollision(Collision* collision) override;

		void Update();
		void OnSpace();
		void OnSpaceUp();
		void Shoot();

		void SmallExplosion();
		void Quit();

	public:

		static const Uint32 s_StreakTime = 1250;
		
		static Uint32 s_Player1LastPawnKillTime;
		static Uint32 s_Player2LastPawnKillTime;
		
		static int s_Player1Streak;
		static int s_Player2Streak;
		
		static int s_Player1MaxStreak;
		static int s_Player2MaxStreak;

		static void NewKill(std::string playerNumber)
		{
			Uint32 ticks = SDL_GetTicks();
			if (playerNumber == "player1")
			{
				Uint32 deltaTicks = ticks - s_Player1LastPawnKillTime;
				LOG(LVL_WARNING, std::to_string(deltaTicks) + " :: " + std::to_string(s_StreakTime));
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
			else if(playerNumber == "player2")
			{
				Uint32 deltaTicks = ticks - s_Player2LastPawnKillTime;
				LOG(LVL_WARNING, std::to_string(deltaTicks) + " :: " + std::to_string(s_StreakTime));
				if (deltaTicks < s_StreakTime)
				{
					s_Player2Streak++;
					if (s_Player2Streak > s_Player2MaxStreak)
						s_Player2MaxStreak = s_Player2Streak;
				}
				else
				{
					s_Player2Streak = 0;
				}
				s_Player2LastPawnKillTime = ticks;
			}		
			else if ("player0")
			{
				//TODO: maybe reduce points or have a PC score you compete against
			}
		}

	};
}