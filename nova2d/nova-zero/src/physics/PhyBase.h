#pragma once
#include "../maths/Vec2.h"
#include "../maths/Vec2Int.h"
#include <string>
#include "Box2D.h"

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

			unsigned int m_CollisionLayer = 0;

		public:


			PhysicsTypes m_Type = PhysicsTypes::PhySprite;
			
		public:

			PhyBase(const std::string colliderName, PhySprite* reference);
			PhyBase(const std::string colliderName, PhySensor* reference);

			PhySprite* GetPhySpriteRef() const;
			PhySensor* GetPhySensorRef() const;

			virtual unsigned int GetPhyID() const = 0;

			std::string GetColliderName() const;
			void SetColliderName(const std::string& colliderName);

			void DestroySelf();

		};
	}
}