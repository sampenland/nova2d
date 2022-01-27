#include "Graver.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		Graver::Graver(int graverGroup, int effectRadius, Vec2Int defaultGraverEffectMag) : Deleteable("graver")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "graver_" + std::to_string(m_ID);
			
			if (graverGroup >= MAX_GRAVER_GROUPS)
			{
				m_GraverGroupKeyID = 0;
			}
			else
			{
				m_GraverGroupKeyID = graverGroup;
			}

			m_GraverEffectRadius = effectRadius;
			m_GraverEffectMagnitude = defaultGraverEffectMag;

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);

		}

		void Graver::GraverUpdate()
		{

		}

		Graver::~Graver()
		{

		}

		void Graver::DestroySelf()
		{
			n2dRemoveDeleteable(m_CleanID);
			Game::s_SceneManager->s_GraverManager->RemoveGraver(m_ID);
		}
	}
}