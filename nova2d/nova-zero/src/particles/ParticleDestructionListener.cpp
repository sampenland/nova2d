#include "ParticleDestructionListener.h"
#include "Box2D/Particle/b2ParticleSystem.h"
#include "../logging/logging.h"
#include "../graphics/Sprite.h"

namespace novazero
{
	namespace particles
	{
		using namespace novazero::graphics;

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
			Sprite* particle = (Sprite*)particleSystem->GetUserDataBuffer()[index];

			if (particle)
			{
				particle->DestroySelf();
			}

			b2DestructionListener::SayGoodbye(particleSystem, index);
		}
	}
}