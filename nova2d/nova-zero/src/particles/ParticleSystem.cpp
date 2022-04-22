#include "ParticleSystem.h"
#include "../core/Game.h"

namespace novazero
{
	namespace particles
	{
		using namespace core;

		ParticleSystem::ParticleSystem(const std::string& spriteTexture, Vec2Int size, 
			int32 maxParticles, float particleRadius, unsigned char layer)
		{
			m_ParticleAssetName = spriteTexture;
			m_AssetSize = size;
			m_Layer = layer;

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
			if (!m_System) return -1;

			b2ParticleDef pd;
			pd.flags = type;
			pd.velocity.Set(velocity.x, velocity.y);
			pd.color.Set((uint8)color.r, (uint8)color.g, (uint8)color.b, (uint8)color.a);
			pd.position.Set(position.x, position.y);
			
			float lifetime = n2dRandomFloat(m_MinLifeTime, m_MaxLifeTime); // Used below
			//pd.lifetime = lifetime; // TODO: handling this myself, maybe I shouldn't
			
			int32 index = m_System->CreateParticle(pd);			
			Sprite* s = new Sprite(m_ParticleAssetName, position, m_AssetSize, m_Layer);
			
			m_Particles[index] = s;

			LOGS("created : " + tostring(index));// TODO: remove
			Timer* t = new Timer(lifetime, false, ([=]() {
				RemoveParticle(index);
			}));

			if(n2dDebugVerbose)
				LOGS("Particle Created: " + tostring(index));

			return index;
		}

		void ParticleSystem::Update()
		{
			const b2Vec2* positions = m_System->GetPositionBuffer();

			for (int i = 0; i < m_System->GetParticleCount(); i++)
			{
				const b2Vec2 pos = positions[i];

				if (m_Particles[i])
					m_Particles[i]->SetPosition(Vec2(pos.x, pos.y));
				else
					m_Particles.erase(i);
			}
		}

		void ParticleSystem::BurstParticles(int32 particleCount, Vec2 burstPosition, Vec2 velocity)
		{
			for (int i = 0; i < particleCount; i++)
			{
				CreateParticle(b2_waterParticle, burstPosition, velocity, *n2dGetColor("white"));
			}
		}

		void ParticleSystem::RemoveParticle(int32 index)
		{
			if (!m_System) return;

			if (m_Particles.find(index) != m_Particles.end())
			{

				if(m_Particles[index])
					m_Particles[index]->DestroySelf();

				m_System->DestroyParticle(index);
				
				m_Particles.erase(index);
				LOGS("removed : " + tostring(index)); // TODO: remove
				if (n2dDebugVerbose)
					LOGS("Particle destroyed: " + tostring(index));
			}
		}

		void ParticleSystem::SetLifetime(float min, float max)
		{
			m_System->SetDestructionByAge(true);
			m_UsingLifetime = true;
			m_MinLifeTime = min;
			m_MaxLifeTime = max;
		}

		int ParticleSystem::ParticleCount()
		{
			if (!m_System) return 0;
			return m_System->GetParticleCount();
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