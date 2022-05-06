#include "PhyContactFilter.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace novazero::core;

		CFilterBase::CFilterBase(CFilterType type, bool willCollide)
			: m_Type(type), m_ShouldCollide(willCollide)
		{
			m_ID = n2dGameGetID();
		}

		PhyContactFilter::PhyContactFilter()
		{

		}

		unsigned int PhyContactFilter::AddContactFilter(b2Fixture* a, b2Fixture* b, bool willCollide)
		{
			CFilterFixtureToFixture* cf = new CFilterFixtureToFixture(a, b, willCollide);
			m_CFilters.push_back(cf);
			return cf->m_ID;
		}

		unsigned int PhyContactFilter::AddContactFilter(b2Fixture* a, b2ParticleSystem* b, int32 pIndex, bool willCollide)
		{
			CFilterFixtureToParticle* cf = new CFilterFixtureToParticle(a, b, pIndex, willCollide);
			m_CFilters.push_back(cf);
			return cf->m_ID;
		}

		unsigned int PhyContactFilter::AddContactFilter(b2ParticleSystem* pSystem, int32 a, int32 b, bool willCollide)
		{
			CFilterParticleToParticle* cf = new CFilterParticleToParticle(pSystem, a, b, willCollide);
			m_CFilters.push_back(cf);
			return cf->m_ID;
		}

		void PhyContactFilter::RemoveContactFilter(unsigned int id)
		{
			for (auto it = m_CFilters.begin(); it != m_CFilters.end(); it++)
			{
				if ((*it)->m_ID == id)
				{
					m_CFilters.erase(it);
					break;
				}
			}
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
				if (contact.m_Fixture == fixture && contact.m_ParticleIndex == particleIndex)
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
					(contact.m_ParticleIndexA == particleIndexA && contact.m_ParticleIndexB == particleIndexB) ||
					(contact.m_ParticleIndexB == particleIndexA && contact.m_ParticleIndexA == particleIndexB))
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