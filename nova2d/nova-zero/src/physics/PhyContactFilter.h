#pragma once
#include "Box2D/Dynamics/b2WorldCallbacks.h"
#include <vector>

namespace novazero
{
	namespace physics
	{
		enum class CFilterType
		{
			FixtureToFixture,
			ParticleToFixture,
			ParticleToParticle
		};

		class CFilterBase
		{
		public:
			CFilterType m_Type;
			bool m_ShouldCollide = true;
		};

		class CFilterFixtureToFixture : public CFilterBase
		{
		public:
			b2Fixture* m_FixtureA;
			b2Fixture* m_FixtureB;
		};

		class CFilterFixtureToParticle : public   CFilterBase
		{
		public:
			b2Fixture* fixture;
			b2ParticleSystem* particleSystem;
			int32 particleIndex;
		};

		class CFilterParticleToParticle : public  CFilterBase
		{
		public:
			b2ParticleSystem* particleSystem;
			int32 particleIndexA;
			int32 particleIndexB;
		};

		class PhyContactFilter : public b2ContactFilter
		{
		private:

			std::vector<CFilterBase*> m_CFilters;

		public:

			PhyContactFilter();

			/// Return true if contact calculations should be performed between these two shapes.
			/// @warning for performance reasons this is only called when the AABBs begin to overlap.
			bool ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB);

			/// Return true if contact calculations should be performed between a
			/// fixture and particle.  This is only called if the
			/// b2_fixtureContactListenerParticle flag is set on the particle.
			bool ShouldCollide(b2Fixture* fixture,
				b2ParticleSystem* particleSystem,
				int32 particleIndex);

			/// Return true if contact calculations should be performed between two
			/// particles.  This is only called if the
			/// b2_particleContactListenerParticle flag is set on the particle.
			bool ShouldCollide(b2ParticleSystem* particleSystem,
				int32 particleIndexA, int32 particleIndexB);

			void DestroySelf();

		};
	}
}