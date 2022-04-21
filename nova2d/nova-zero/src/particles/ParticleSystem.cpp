#include "ParticleSystem.h"
#include "../core/Game.h"

namespace novazero
{
	namespace particles
	{
		using namespace core;

		ParticleSystem::ParticleSystem(int32 maxParticles, float particleRadius)
		{
			b2ParticleSystemDef psDef;

			if (n2dGetCurrentWorld())
			{
				m_System = n2dGetCurrentWorld()->CreateParticleSystem(&psDef);
				m_System->SetMaxParticleCount(maxParticles);
				m_System->SetRadius(particleRadius);
			}
			else
			{
				LOGO(LVL_NFE, "Particle system not created.");
			}
		}

		int32 ParticleSystem::CreateParticle(b2ParticleFlag type, Vec2 position, Vec2 velocity, Color color)
		{
			if (!m_System)return;

			b2ParticleDef pd;
			pd.flags = type;
			pd.velocity.Set(velocity.x, velocity.y);
			pd.color.Set((uint8)color.r, (uint8)color.g, (uint8)color.b, (uint8)color.a);
			pd.position.Set(position.x, position.y);
			
			int32 index = m_System->CreateParticle(pd);
			
			m_ParticleIndices.push_back(index);

			return index;
		}

		void ParticleSystem::DestroyParticle(int32 index)
		{
			if (!m_System)return;

			if (std::find(m_ParticleIndices.begin(), m_ParticleIndices.end(), index) != m_ParticleIndices.end())
			{
				m_System->DestroyParticle(index);
			}
		}

		void ParticleSystem::SetLifetime(float min, float max)
		{
			m_UsingLifetime = true;
			m_MinLifeTime = min;
			m_MaxLifeTime = max;
		}

		void ParticleSystem::DestroySelf()
		{
			if (n2dGetCurrentWorld())
			{
				n2dGetCurrentWorld()->DestroyParticleSystem(m_System);
			}
		}
	}
}