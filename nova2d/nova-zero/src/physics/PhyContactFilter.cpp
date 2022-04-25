#include "PhyContactFilter.h"

namespace novazero
{
	namespace physics
	{

		PhyContactFilter::PhyContactFilter()
		{

		}

		/// Return true if contact calculations should be performed between these two shapes.
		/// @warning for performance reasons this is only called when the AABBs begin to overlap.
		bool PhyContactFilter::ShouldCollide(b2Fixture* fixtureA, b2Fixture* fixtureB)
		{

			for (CFilterBase* cf : m_CFilters)
			{
				if (cf->m_Type != CFilterType::FixtureToFixture)
					continue;

				CFilterFixtureToFixture& contact = *(CFilterFixtureToFixture*)cf;
				if (
					(contact.m_FixtureA == fixtureA && contact.m_FixtureB == fixtureB) ||
					(contact.m_FixtureB == fixtureA && contact.m_FixtureA == fixtureB))
				{
					return contact.m_ShouldCollide;
				}

			}

			// Default collision ON
			return true;
		}

		/// Return true if contact calculations should be performed between a
		/// fixture and particle.  This is only called if the
		/// b2_fixtureContactListenerParticle flag is set on the particle.
		bool PhyContactFilter::ShouldCollide(b2Fixture* fixture,
			b2ParticleSystem* particleSystem,
			int32 particleIndex)
		{
			for (CFilterBase* cf : m_CFilters)
			{
				if (cf->m_Type != CFilterType::ParticleToFixture)
					continue;

				CFilterFixtureToParticle& contact = *(CFilterFixtureToParticle*)cf;
				if (contact.fixture == fixture && contact.particleIndex == particleIndex)
				{
					return contact.m_ShouldCollide;
				}

			}

			// Default collision OFF
			return false;
		}

		/// Return true if contact calculations should be performed between two
		/// particles.  This is only called if the
		/// b2_particleContactListenerParticle flag is set on the particle.
		bool PhyContactFilter::ShouldCollide(b2ParticleSystem* particleSystem,
			int32 particleIndexA, int32 particleIndexB)
		{
			for (CFilterBase* cf : m_CFilters)
			{
				if (cf->m_Type != CFilterType::ParticleToParticle)
					continue;

				CFilterParticleToParticle& contact = *(CFilterParticleToParticle*)cf;
				if (
					(contact.particleIndexA == particleIndexA && contact.particleIndexB == particleIndexB) ||
					(contact.particleIndexB == particleIndexA && contact.particleIndexA == particleIndexB))
				{
					return contact.m_ShouldCollide;
				}

			}

			// Default collision OFF
			return false;
		}

		void PhyContactFilter::DestroySelf()
		{
			m_CFilters.clear();
		}
	}
}