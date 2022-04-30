#include "PhySimpleDirectional.h"
#include "../../core/Game.h"
#include "../../core/Timer.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace maths;
			using namespace core;

			PhySimpleDirectional::PhySimpleDirectional(Vec2 direction, float speed, float autoDestroySeconds,
				const std::string& assetName, Vec2 position, Vec2 size,
				unsigned char layer, Vec2Int displaySize, std::string colliderName,
				const std::string& collisionGroup)
				: m_Direction(direction), m_Speed(speed), m_DestroyTime(autoDestroySeconds),
				PhySprite(assetName, position, size, layer, displaySize, colliderName, collisionGroup)
			{

				auto cleanID = n2dAddUpdater(PhySimpleDirectional::Update, this);
				m_CleanUpdaters.push_back(cleanID);

				if (GetPhySprite())
				{
					GetPhySprite()->ConfigurePhysicsCircle(false, size.x);
					if (GetPhySprite()->GetBody())
					{
						GetPhySprite()->GetBody()->SetBullet(true);
						GetPhySprite()->GetBody()->SetLinearVelocity(
							b2Vec2(direction.x * speed * PHYSICS_MULTIPLIER * 10, direction.y * speed * PHYSICS_MULTIPLIER * 10)
						);
					}
				}

				Timer* t = new Timer(autoDestroySeconds * 1000.f, false, n2dMakeFunc(PhySimpleDirectional::DestroySelf, this));

			}

			void PhySimpleDirectional::Update()
			{

			}

			void PhySimpleDirectional::DestroySelf()
			{
				CleanUpdaters();
				PhySprite::DestroySelf();
				SetDeleted(true);
			}
		}
	}
}