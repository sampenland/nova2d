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