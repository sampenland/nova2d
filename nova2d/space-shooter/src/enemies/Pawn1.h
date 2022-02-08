#pragma once
#include "ai/SimpleWeakAI.h"

namespace spaceshooter
{
	using namespace novazero::ai;

	class Pawn1 : public SimpleWeakAI
	{

	private:

		std::string m_KilledBy = "";

	protected:

	public:

		Pawn1(Vec2 position);

		void Hurt(int damage, const std::string& damager);
		void Shoot();

	};
}