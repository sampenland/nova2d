#pragma once
#include "ai/SimpleWeakAI.h"

namespace spaceshooter
{
	using namespace novazero::ai;

	class Pawn1 : public SimpleWeakAI
	{

	private:

	protected:

	public:

		Pawn1(Vec2 position);

		void DisplayHit(int damage);
		void Hurt(int damage);
		void Shoot();

	};
}