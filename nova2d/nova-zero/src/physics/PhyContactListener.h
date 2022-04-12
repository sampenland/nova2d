#pragma once
#include "box2d/box2d.h"
#include "box2d/b2_contact.h"

namespace novazero
{
	namespace physics
	{
		class PhyContactListener : public b2ContactListener
		{

		private:

		public:

			PhyContactListener() {};

			virtual void BeginContact(b2Contact* contact) = 0;
			virtual void EndContact(b2Contact* contact) = 0;

		};
	}
}