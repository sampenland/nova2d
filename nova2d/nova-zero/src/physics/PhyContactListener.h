#pragma once
#include "box2d/box2d.h"
#include "box2d/b2_contact.h"
#include <map>
#include <functional>
#include "PhyBase.h"

namespace novazero
{
	namespace physics
	{
		struct PhyCollision
		{
			PhyBase* m_ContactA = nullptr;
			PhyBase* m_ContactB = nullptr;
			std::function<void(PhyBase* a, PhyBase* b)> f_OnEnter = nullptr;
			std::function<void(PhyBase* a, PhyBase* b)> f_OnExit = nullptr;
		};

		class PhyContactListener : public b2ContactListener
		{

		private:

			std::map<unsigned int, PhyCollision*> m_Collisions;

		public:

			PhyContactListener();

			unsigned int AddCollision(PhyBase* contactA, PhyBase* contactB, 
				std::function<void(PhyBase* a, PhyBase* b)> onEnter,
				std::function<void(PhyBase* a, PhyBase* b)> onExit);

			void RemoveCollision(unsigned int id);

			void BeginContact(b2Contact* contact);
			void EndContact(b2Contact* contact);

		};
	}
}