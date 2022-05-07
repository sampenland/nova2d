#include "Particle.h"
#include "ParticleSystem.h"
#include "../core/Game.h"

namespace novazero
{
	namespace particles
	{
		using namespace core;

		Particle::Particle(Sprite* sprite, ParticleSystem* pSystem)
			: m_Sprite(sprite), m_PSystem(pSystem)
		{
			
		}

		void Particle::SetIndex(int index)
		{
			m_Index = index;
		}

		void Particle::UpdatePosition(float x, float y)
		{
			m_Sprite->SetPosition(Vec2(x, y));
		}

		void Particle::DestroySelf()
		{
			if (n2dDebugVerbose)
			{
				LOGS("[Deleted Particle_" + tostring(m_Index) + " ]");
			}

			if (m_Sprite)
				m_Sprite->DestroySelf();
		}
	}
}