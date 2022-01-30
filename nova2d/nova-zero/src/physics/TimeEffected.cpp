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
			SetTimeEffectEnabled(false);
		};

		TimeEffected::~TimeEffected()
		{
			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffected(this);
		}

		void TimeEffected::ConfigureTimeEffected(Positional* positional)
		{
			if (m_Physical)
				delete m_Physical;
			m_Physical = positional;

			SetTimeEffectEnabled(true);
			Game::s_SceneManager->s_TimeEffectorManager->AddEffected(this);
		}
	}
}