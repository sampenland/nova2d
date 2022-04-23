#include "ParticleDestructionListener.h"
#include "Particle.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace particles
	{
		ParticleDestructionListener::ParticleDestructionListener()
			: b2DestructionListener()
		{ }

		void ParticleDestructionListener::SayGoodbye(b2Joint* joint)
		{
			
		}

		void ParticleDestructionListener::SayGoodbye(b2Fixture* fixture)
		{
			
		}

		void ParticleDestructionListener::SayGoodbye(b2ParticleSystem* particleSystem, int32 index)
		{
			Particle* particle = (Particle*)particleSystem->GetUserDataBuffer()[index];

			if (particle)
			{
				particle->DestroySelf();
			}

			b2DestructionListener::SayGoodbye(particleSystem, index);
		}
	}
}