#pragma once
#include "Collision.h"
#include "Collider.h"

namespace novazero
{
	namespace physics
	{
		class Collision
		{

		public:

			Collider* m_ColliderA;
			Collider* m_ColliderB;

			Collision() {};

			Collision(Collider* a, Collider* b)
			{
				m_ColliderA = a;
				m_ColliderB = b;
			}

			~Collision()
			{
				if (m_ColliderA)
					delete m_ColliderA;

				if (m_ColliderB)
					delete m_ColliderB;;
			}

		};
	}
}