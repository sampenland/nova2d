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

			unsigned int m_ID = 0;

			CFilterType m_Type;
			bool m_ShouldCollide = true;
			
			CFilterBase(CFilterType type, bool willCollide);;
		};

		class CFilterFixtureToFixture : public CFilterBase
		{

		public:

			b2Fixture* m_FixtureA;
			b2Fixture* m_FixtureB;

			CFilterFixtureToFixture(b2Fixture* a, b2Fixture* b, bool willCollide)
				: CFilterBase(CFilterType::FixtureToFixture, willCollide)
			{
				m_FixtureA = a;
				m_FixtureB = b;
			};

		};

		class CFilterFixtureToParticle : public   CFilterBase
		{

		public:

			b2Fixture* m_Fixture;
			b2ParticleSystem* m_ParticleSystem;
			int32 m_ParticleIndex;

			CFilterFixtureToParticle(b2Fixture* a, b2ParticleSystem* b, int32 pIndex, bool willCollide)
				: CFilterBase(CFilterType::ParticleToFixture, willCollide)
			{
				m_Fixture = a;
				m_ParticleSystem = b;
				m_ParticleIndex = pIndex;
			};

		};

		class CFilterParticleToParticle : public  CFilterBase
		{

		public:

			b2ParticleSystem* m_ParticleSystem;
			int32 m_ParticleIndexA;
			int32 m_ParticleIndexB;

			CFilterParticleToParticle(b2ParticleSystem* pSystem, int32 a, int32 b, bool willCollide)
				: CFilterBase(CFilterType::ParticleToParticle, willCollide)
			{
				m_ParticleSystem = pSystem;
				m_ParticleIndexA = a;
				m_ParticleIndexB = b;
			};

		};

		class PhyContactFilter : public b2ContactFilter
		{
		private:

			std::vector<CFilterBase*> m_CFilters;

		public:

			PhyContactFilter();

			unsigned int AddContactFilter(b2Fixture* a, b2Fixture* b, bool willCollide);

			unsigned int AddContactFilter(b2Fixture* a, b2ParticleSystem* b, int32 pIndex, bool willCollide);

			unsigned int AddContactFilter(b2ParticleSystem* pSystem, int32 a, int32 b, bool willCollide);

			void RemoveContactFilter(unsigned int id);

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