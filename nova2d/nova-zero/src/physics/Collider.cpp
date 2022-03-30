#pragma once
#include "Collider.h"

#include "../core/Game.h"

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

			m_CleanID = n2dAddUpdater(Collider::Update, this);
		}

		Collider::~Collider()
		{
			n2dRemoveUpdater(m_CleanID);
			SceneManager::s_CollisionManager->RemoveCollider(this); // TODO: am i making pointers with new and need to delete in manager?
		}

		void Collider::ConfigurePhysicsPositional(Positional* positional)
		{
			if (positional)
			{
				m_AttachedPositional = positional;
			}
		}

		void Collider::Update()
		{
			if (m_AttachedPositional)
			{
				if(m_Velocity != Vec2(0, 0))
					HandleFriction();
				
				if (m_AttachedPositional->GetDrawable())
				{
					Vec2 position = m_AttachedPositional->GetDrawable()->GetPosition();
					Vec2 newPosition = position.add(n2dGravity);
					m_AttachedPositional->SetPosition(newPosition);
					m_AttachedPositional->GetDrawable()->SetPosition(newPosition);
				}
			}
		}

		void Collider::HandleFriction()
		{
			if (m_Velocity.x != 0)
			{
				if (m_Velocity.x < 0)
					m_Velocity.x += m_Friction;

				if (m_Velocity.x > 0)
					m_Velocity.x -= m_Friction;
			}

			if (m_Velocity.y != 0)
			{
				if (m_Velocity.y < 0)
					m_Velocity.y += m_Friction;

				if (m_Velocity.y > 0)
					m_Velocity.y -= m_Friction;
			}
		}
			
		void Collider::ConfigureCollider(Sprite* sprite, int collisionLayer, const std::string& colliderName)
		{
			m_UsingCollider = true;

			m_CollisionLayer = collisionLayer;
			m_ColliderSprite = sprite;
			m_ColliderName = colliderName;

			SceneManager::s_CollisionManager->AddCollider(this);
		}

		void Collider::ConfigureCollider(Sprite* sprite, int collisionLayer, const std::string& colliderName, Positional* positional)
		{
			m_UsingCollider = true;

			m_CollisionLayer = collisionLayer;
			m_ColliderSprite = sprite;
			m_ColliderName = colliderName;

			SceneManager::s_CollisionManager->AddCollider(this);
			ConfigurePhysicsPositional(positional);
		}

		void Collider::SetFriction(float friction)
		{
			m_Friction = friction;
		}

		void Collider::SetVelocity(Vec2 vel)
		{
			m_Velocity = vel;
		}

		void Collider::AddVelocity(Vec2 vel)
		{
			m_Velocity.add(vel);
		}
	}
}