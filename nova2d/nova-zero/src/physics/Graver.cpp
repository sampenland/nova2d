#include "Graver.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		Graver::Graver(int graverGroup)
		{
			m_ID = n2dGameGetID();
			
			if (graverGroup >= MAX_GRAVER_GROUPS)
			{
				m_GraverGroupKeyID = 0;
			}
			else
			{
				m_GraverGroupKeyID = graverGroup;
			}
		}

		Graver::~Graver()
		{

		}

		void Graver::GraverUpdate()
		{

		}
	}
}