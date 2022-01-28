#include "Graver.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		Graver::Graver() : Deleteable("graver") 
		{
			m_ID = n2dGameGetID();

			m_GraverGroupKeyID = 0;
			m_GraverEffectRadius = 1;
			m_GraverEffectMagnitude = Vec2Int(0, 0);

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);
		};

		Graver::Graver(GraverType type, int graverGroup, int effectRadius, 
			Vec2Int defaultGraverEffectMag) : Deleteable("graver")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "graver_" + std::to_string(m_ID);
			
			m_GraverType = type;

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

		void Graver::ConfigureGraver(GraverType type, int graverGroup, int effectRadius, 
			Vec2Int defaultGraverEffectMag)
		{
			m_GraverType = type;

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
			Game::s_SceneManager->s_GraverManager->RemoveGraver(this);
			CleanUpdaters();
			m_DeleteNow = 1;
		}
	}
}