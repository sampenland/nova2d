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
			m_CollisionLayer = collisionLayer;
			m_ID = Game::GetNextID();
		}
			
		void Collider::Configure(Sprite* sprite, f_CollisionPassFunction onCollision)
		{
			m_Sprite = sprite;
			f_OnCollision = onCollision;
		}
	}
}