#pragma once
#include "../maths/Vec2.h"
#include "../maths/Vec2Int.h"
#include <string>

namespace novazero
{
	namespace physics
	{
		using namespace maths;

		class PhySprite;
		class PhySensor;

		enum class PhysicsTypes
		{
			PhySprite,
			PhySensor
		};

		class PhyBase
		{

		private:

			std::string m_PhyColliderName = "phyObj";

			PhySprite* m_PhySprite = nullptr;
			PhySensor* m_PhySensor = nullptr;

		public:

			b2Body* m_Body = nullptr;
			PhysicsTypes m_Type = PhysicsTypes::PhySprite;

			PhySprite* GetPhySpriteRef() const
			{
				return m_PhySprite;
			}

			PhySensor* GetPhySensorRef() const
			{
				return m_PhySensor;
			}

			Vec2 m_PhySize = Vec2(0, 0);
			float m_Radius = 1.f;

			b2FixtureDef fixtureDef;
			float m_Density = 1.f;
			float m_Friction = 1.f;
			bool m_IsSensor = 1.f;
			float m_Restitution = 1.f;
			float m_RestitutionThres = 1.f;
			
		public:

			PhyBase(const std::string colliderName, PhySprite* reference) 
			{
				m_PhyColliderName = colliderName;
				m_Type = PhysicsTypes::PhySprite;
				m_PhySprite = reference;
			};

			PhyBase(const std::string colliderName, PhySensor* reference)
			{
				m_PhyColliderName = colliderName;
				m_Type = PhysicsTypes::PhySprite;
				m_PhySensor = reference;
			};

			std::string GetColliderName() const
			{
				return m_PhyColliderName;
			}
		};
	}
}