#pragma once
#include <vector>

namespace novazero
{
	namespace physics
	{
		class Collider;

		class CollisionManager
		{

		private:

			std::vector<Collider*> m_Colliders = { };

		public:

			CollisionManager();
			~CollisionManager();

			void ClearColliders();

			void AddCollider(Collider* object);
			void RemoveCollider(Collider* collider);

			void Update();
		};
	}
}