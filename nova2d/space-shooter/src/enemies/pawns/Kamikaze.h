#pragma once
#include "ai/SimpleWeakAI.h"

namespace spaceshooter
{
	using namespace novazero::ai;

	class Kamikaze : 
		public SimpleWeakAI
	{

	private:

		unsigned int m_CleanID = 0;

	public:

		Kamikaze(Vec2 position, float* speedRef);

		void Hurt(int damage);
		void SmallExplosion();
		void DisplayHit(int damage);

		void DestroySelf();

	};
}