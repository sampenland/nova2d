#pragma once
#include <vector>
#include "Collider.h"

namespace novazero
{
	namespace physics
	{
		class CollisionManager
		{

		private:

			std::vector<Collider*> m_Colliders = { };

		public:

			CollisionManager();
			~CollisionManager();

			void AddCollider(Collider* object);
			void RemoveCollider(Collider* collider);

			void Update();
		};
	}
}