#pragma once
#include "Collider.h"
#include "../core/Game.h"
#include "Collision.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;
		using namespace graphics;

		Collider::Collider(int collisionLayer)
		{
			m_ColliderSprite = nullptr;
			m_CollisionLayer = collisionLayer;

			m_ID = Game::GetNextID();
		}

		Collider::~Collider()
		{
			SceneManager::s_CollisionManager->RemoveCollider(this);
		}
			
		void Collider::ConfigureCollider(Sprite* sprite, int collisionLayer, std::string colliderName)
		{
			m_UsingCollider = true;

			m_CollisionLayer = collisionLayer;
			m_ColliderSprite = sprite;
			m_ColliderName = colliderName;

			SceneManager::s_CollisionManager->AddCollider(this);
		}
	}
}