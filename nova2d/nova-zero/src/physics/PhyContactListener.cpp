#pragma once
#include "PhyContactListener.h"
#include "../physics/PhyBase.h"
#include "../logging/logging.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace novazero::physics;
		using namespace novazero::core;

		PhyContactListener::PhyContactListener() {};

		unsigned int PhyContactListener::AddCollision(PhyBase* self, PhyBase* other, 
			std::function<void(PhyBase* a, PhyBase* b)> onEnter,
			std::function<void(PhyBase* a, PhyBase* b)> onExit)
		{
			unsigned int id = n2dGameGetID();

			PhyCollision* collision = new PhyCollision();
			collision->m_ContactA = self;
			collision->m_ContactB = other;
			collision->f_OnEnter = onEnter;
			collision->f_OnExit = onExit;

			if (n2dDebugVerbose)
				LOGS("Added collision: " + self->GetColliderName() + "[" + tostring(self->GetPhyID()) + "]" +
					" : " + other->GetColliderName() + "[" + tostring(other->GetPhyID()) + "]");

			m_Collisions[id] = collision;
			return id;

		}

		void PhyContactListener::RemoveCollision(unsigned int id)
		{
			if (m_Collisions.end() != m_Collisions.find(id))
			{
				auto f = m_Collisions.find(id);
				m_Collisions.erase(f);
			}
		}

		void PhyContactListener::BeginContact(b2Contact* contact)
		{
			PhyBase* self = reinterpret_cast<PhyBase*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
			PhyBase* other = reinterpret_cast<PhyBase*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			if (!self || !other) return;

			unsigned int selfID = self->GetPhyID();
			unsigned int otherID = other->GetPhyID();

			if (n2dDebugVerbose)
				LOGS("Contact: " + self->GetColliderName() + "[" + tostring(selfID) + "] : " +
					other->GetColliderName() + "[" + tostring(otherID) + "]");

			if (m_Collisions.find(self->GetPhyID()) != m_Collisions.end() &&
				m_Collisions.find(other->GetPhyID()) != m_Collisions.end())
			{
				if(m_Collisions.find(self->GetPhyID())->second->f_OnEnter)
					m_Collisions.find(self->GetPhyID())->second->f_OnEnter(self, other);
				
				if(m_Collisions.find(other->GetPhyID())->second->f_OnEnter)
					m_Collisions.find(other->GetPhyID())->second->f_OnEnter(other, self);
			}
			
		}

		void PhyContactListener::EndContact(b2Contact* contact)
		{
			PhyBase* self = reinterpret_cast<PhyBase*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
			PhyBase* other = reinterpret_cast<PhyBase*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

			if (!self || !other) return;
			
			if (m_Collisions.find(self->GetPhyID()) != m_Collisions.end() &&
				m_Collisions.find(other->GetPhyID()) != m_Collisions.end())
			{
				if (m_Collisions.find(self->GetPhyID())->second->f_OnExit)
					m_Collisions.find(self->GetPhyID())->second->f_OnExit(self, other);

				if (m_Collisions.find(other->GetPhyID())->second->f_OnExit)
					m_Collisions.find(other->GetPhyID())->second->f_OnExit(other, self);
			}
		}
	}
}