#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"

namespace novazero
{
	namespace particles
	{
		class ParticleDestructionListener :
			public b2DestructionListener
		{

		private:

		public:

			ParticleDestructionListener();

			void SayGoodbye(b2Joint* joint) override;

			void SayGoodbye(b2Fixture* fixture) override;

			void SayGoodbye(b2ParticleSystem* particleSystem, int32 index) override;

		};
	}
}