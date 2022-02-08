#pragma once
#include "core/Timer.h"
#include <vector>

namespace spaceshooter
{
	using namespace novazero::core;

	class Pawn1;

	class Pawn1Controller
	{

	private:

		std::vector<Pawn1*> m_Pawn1s;
		Timer* m_Pawn1Timer = nullptr;

	protected:
	public:

		Pawn1Controller();

		void CreatePawn1();

		void DestroySelf();
	};
}