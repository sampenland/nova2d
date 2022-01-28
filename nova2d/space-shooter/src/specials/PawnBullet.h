#pragma once
#include "controllers/SimpleBulletController.h"
#include "maths/Vec2Int.h"
#include "physics/Graver.h"

namespace spaceshooter
{
	using namespace novazero::controllers;
	using namespace novazero::physics;

	class PawnBullet : 
		public SimpleBulletController, 
		public Graver
	{

	private:

		unsigned int m_CleanID = 0;

	public:

		PawnBullet(Vec2Int start, Vec2Int end, float moveUpdateDelay, Sprite* sprite) : 
			SimpleBulletController(start, end, moveUpdateDelay)
		{
			AddSprite("pawn-bullet", Vec2Int(sprite->GetX(), sprite->GetY() + 32), Vec2Int(16, 16), 0);
			ConfigureCollider(GetSprite(), 0, "pawn-bullet");
			Configure(3, Rect(-16, -16, Game::s_Width + 16, Game::s_Height + 16));
			ConfigureGraver(GraverType::Vec2Force, 0, Vec2Int(0, 0), GetSprite());

		}

		void DestroySelf()
		{
			Graver::DestroySelf();
			SimpleBulletController::DestroySelf();
		}

		~PawnBullet() 
		{
			
		};

	};
}