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
			pd.flags = type | b2_destructionListenerParticle;
			pd.velocity.Set(velocity.x, velocity.y);
			pd.color.Set((uint8)color.r, (uint8)color.g, (uint8)color.b, (uint8)color.a);
			pd.position.Set(position.x, position.y);
			
			Sprite* sprite = new Sprite(m_ParticleAssetName, position, m_AssetSize, m_Layer);
			Particle* particle = new Particle(sprite, this);
			pd.userData = (void*)particle;
			
			float lifetime = n2dRandomFloat(m_MinLifeTime, m_MaxLifeTime);
			pd.lifetime = lifetime; 

			int32 index = m_System->CreateParticle(pd);			
			particle->SetIndex(index);

			m_Particles[index] = particle;

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
				{
					m_Particles[i]->UpdatePosition(pos.x, pos.y);
				}
				else
				{
					m_Particles.erase(i);
				}
			}
		}

		void ParticleSystem::BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity)
		{
			for (int i = 0; i < particleCount; i++)
			{
				Vec2 vel = Vec2(n2dRandomFloat(0.f, 1.f), n2dRandomFloat(0.f, 1.f));
				vel.multiply(Vec2(velocity, velocity));
				CreateParticle(b2_waterParticle, burstPosition, vel, *n2dGetColor("white"));
			}
		}

		void ParticleSystem::RemoveParticle(int32 index)
		{
			if (!m_System) return;

			if (m_Particles.find(index) != m_Particles.end())
			{
				m_System->DestroyParticle(index);				
				m_Particles.erase(index);

				if (n2dDebugVerbose)
					LOGS("Particle custom removed: " + tostring(index));
			}
			else
			{
				LOGS("Unknown particle");
			}
		}

		void ParticleSystem::SetLifetime(float minSeconds, float maxSeconds)
		{
			m_System->SetDestructionByAge(true);
			m_UsingLifetime = true;
			m_MinLifeTime = minSeconds;
			m_MaxLifeTime = maxSeconds;
		}

		int32 ParticleSystem::ParticleCount()
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