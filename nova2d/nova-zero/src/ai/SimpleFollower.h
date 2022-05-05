#pragma once
#include "../core/EventListener.h"
#include "../maths/Rect.h"
#include "../core/BoundUser.h"
#include "../core/TimerWatcher.h"
#include "../core/Meta.h"
#include "../physics/PhySprite.h"
#include "../physics/PhySensor.h"
#include "../core/Positional.h"
#include "../core/NovaCore.h"

namespace novazero
{
	namespace ai
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;
		using namespace physics;

		class SimpleFollower : 
			public EventListener,
			public BoundUser,
			public Positional,
			public TimerWatcher,
			public Meta
		{

		private:

			Positional* m_Target;
			Vec2Int m_ScatterOffset = NULLVEC2INT;
			float m_DelayScatter = 0;
			float m_WaitAtTargetMin = 8.f;
			float m_WaitAtTargetMax = 15.f;
			float m_InRange = 0.f;
			bool m_AtTarget = false;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;
			int m_LookAtDegAdd = 0;
			float m_WaitDelay = 0;
			Vec2Int m_WaitTarget;
			bool m_LookAtTarget = false;

			float m_MoveAngleDegrees = 0.f;
			
		protected:

			Sprite* m_Sprite = nullptr;
			PhySprite* m_PhySprite = nullptr;
			PhySensor* m_Sensor = nullptr;

			float m_MoveSpeed = 0;

		public:

			SimpleFollower(Positional* target, const float moveUpdateDelayMS);

			void AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);
			void AddPhySprite(const std::string& assetName, Vec2 position, Vec2 size, 
				unsigned char layer, Vec2Int displaySize, const std::string& colliderName, const std::string& collisionGroup = "none");

			void AddPhySensor(std::string colliderName, bool staticBody, Vec2 position, 
				Vec2 size, const std::string& collisionGroup, float density = 0.5f, float friction = 0.3f);
			void AddPhySensor(std::string colliderName, bool staticBody, Vec2 position,
				std::vector<Vec2> shapeVertices, const int vertexCount, const std::string& collisionGroup,
				float density = 0.5f, float friction = 0.3f);
			void AddPhySensor(std::string colliderName, bool staticBody,
				Vec2 position, float radius, const std::string& collisionGroup = "none", float density = 0.5f, float friction = 0.3f);

			Sprite* GetSprite() const { return m_Sprite; }
			PhySensor* GetPhySensor() const { return m_Sensor; }
			PhySprite* GetPhySprite() const { return m_PhySprite; }

			void Configure(float moveSpeed, float delayStart = 0.0f, Vec2Int waitTargetPos = Vec2Int(0,0));
			void ConfigureInRange(float distanceToBeInRange);
			void ConfigureTarget(Positional* target);
			void ConfigureWaitAtTarget(float min, float max);
			void ConfigureRotation(bool lookAtTarget, int addToLookAtDeg) { m_LookAtTarget = lookAtTarget; m_LookAtDegAdd = addToLookAtDeg; }
			void ConfigureScatterOffset(Vec2Int offset) { m_ScatterOffset = offset; }
			
			Positional* GetTarget() const;

			float GetMoveAngleDegrees() const
			{
				return m_MoveAngleDegrees;
			}

			void UpdateFollower();

			void DestroySelf() override;

		};
	}
}