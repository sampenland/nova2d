#pragma once
#include "../core/Deleteable.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		TimeEffected::TimeEffected()
		{
			m_ID = n2dGameGetID();
			m_Physical = new Positional();
			m_Physical->SetPosition(Game::GetCenterScreen());
		};
	}
}