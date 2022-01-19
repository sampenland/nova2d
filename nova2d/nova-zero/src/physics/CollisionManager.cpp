#include "CollisionManager.h"
#include "Collision.h"
#include "../logging/logging.h"

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
			// Todo: clean up on m_Colliders, not happening when they go off screen
			int colliders = m_Colliders.size();
			if (colliders < 2) return;

			std::vector<Collision> collisions;

			bool checking = true;

			int left = 0;
			int right = 1;
			while (right < colliders)
			{
				for (int i = right; i < colliders; i++)
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
						collisions.push_back(colli);
					}

				}

				left += 1;
				right = left + 1;
			}

			for (size_t i = 0; i < collisions.size(); i++)
			{
				if (collisions[i].m_ColliderA->f_OnCollision != nullptr)
				{
					collisions[i].m_ColliderA->f_OnCollision(&collisions[i]);
				}
				else
				{
					collisions[i].m_ColliderA->OnCollision(&collisions[i]);
				}

				if (collisions[i].m_ColliderB->f_OnCollision != nullptr)
				{
					collisions[i].m_ColliderB->f_OnCollision(&collisions[i]);
				}
				else
				{
					collisions[i].m_ColliderB->OnCollision(&collisions[i]);
				}
			}
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