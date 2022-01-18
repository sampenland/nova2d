#include "CollisionManager.h"
#include "Collision.h"

namespace novazero
{
	namespace physics
	{
		CollisionManager::CollisionManager()
		{

		}

		CollisionManager::~CollisionManager()
		{

		}

		void CollisionManager::Update()
		{
			int maxPossibleCollisions = m_Colliders.size();
			
			if (maxPossibleCollisions < 2) return;

			Collision* collisions = new Collision[maxPossibleCollisions];
			memset(collisions, 0, maxPossibleCollisions);

			bool checking = true;

			int totalCollisions = 0;
			int left = 0;
			int right = 1;
			while (right < maxPossibleCollisions)
			{
				for (int i = right; i < maxPossibleCollisions; i++)
				{
					Collider* a = m_Colliders.at(left);
					Collider* b = m_Colliders.at(i);

					if (a->m_ID == b->m_ID) continue;
					if (a->m_CollisionLayer != b->m_CollisionLayer) continue;

					if (a->m_ColliderSprite->GetX() < b->m_ColliderSprite->GetX() + b->m_ColliderSprite->GetWidth() &&
						a->m_ColliderSprite->GetX() + a->m_ColliderSprite->GetWidth() > b->m_ColliderSprite->GetX() &&
						a->m_ColliderSprite->GetY() < b->m_ColliderSprite->GetY() + b->m_ColliderSprite->GetHeight() &&
						a->m_ColliderSprite->GetY() + a->m_ColliderSprite->GetHeight() > b->m_ColliderSprite->GetY())
					{
						Collision colli(a, b);
						collisions[totalCollisions] = colli;
						totalCollisions++;
					}

				}

				left += 1;
				right = left + 1;
			}

			for (int i = 0; i < totalCollisions; i++)
			{
				collisions[i].m_ColliderA->OnCollision(&collisions[i]);
				collisions[i].m_ColliderB->OnCollision(&collisions[i]);
			}

			delete[] collisions;
		}

		void CollisionManager::AddCollider(Collider* collider)
		{
			std::vector<Collider*>::iterator f = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
			if (f != m_Colliders.end()) return;

			m_Colliders.push_back(collider);

		}

		void CollisionManager::RemoveCollider(Collider* collider)
		{
			std::vector<Collider*>::iterator f = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
			if (f != m_Colliders.end()) 
			{
				m_Colliders.erase(f);
			}
		}
	}
}