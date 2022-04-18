#pragma once
#include "PhyBase.h"
#include "../core/Game.h"
#include "PhySensor.h"
#include "PhySprite.h"

namespace novazero
{
	namespace physics
	{
		PhyBase::PhyBase(const std::string colliderName, PhySprite* reference)
		{
			m_PhyColliderName = colliderName;
			m_Type = PhysicsTypes::PhySprite;
			m_PhySprite = reference;
		};

		PhyBase::PhyBase(const std::string colliderName, PhySensor* reference)
		{
			m_PhyColliderName = colliderName;
			m_Type = PhysicsTypes::PhySprite;
			m_PhySensor = reference;
		};

		PhySprite* PhyBase::GetPhySpriteRef() const
		{
			return m_PhySprite;
		}

		PhySensor* PhyBase::GetPhySensorRef() const
		{
			return m_PhySensor;
		}	

		void PhyBase::DestroySelf()
		{
			if (m_PhySprite)
			{
				m_PhySprite->DestroySelf();
			}

			if (m_PhySensor)
			{
				m_PhySensor->DestroySelf();
			}
		}

		std::string PhyBase::GetColliderName() const
		{
			return m_PhyColliderName;
		}
	}
}