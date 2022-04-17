#pragma once
#include "../maths/Vec2.h"
#include "../maths/Vec2Int.h"
#include <string>

namespace novazero
{
	namespace physics
	{
		using namespace maths;

		class PhyBase
		{

		public:

			b2Body* m_Body = nullptr;

			Vec2 m_PhySize = Vec2(0, 0);
			float m_Radius = 1.f;
			b2FixtureDef fixtureDef;
			float m_Density = 1.f;
			float m_Friction = 1.f;
			bool m_IsSensor = 1.f;
			float m_Restitution = 1.f;
			float m_RestitutionThres = 1.f;

			std::string m_PhyColliderName = "phyobj";
			
		public:

			PhyBase(const std::string colliderName) 
			{
				m_PhyColliderName = colliderName;
			};

			std::string GetColliderName() const
			{
				return m_PhyColliderName;
			}
		};
	}
}