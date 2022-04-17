#include "PhySimpleFollower.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			PhySimpleFollower::PhySimpleFollower(Positional* target, float moveDelay) :
				SimpleFollower(target, moveDelay)
			{
				if (!target)
				{
					LOG(LVL_W, "PhySimpleFollower has no target");
				}

				auto cid = n2dAddUpdater(PhySimpleFollower::Update, this);
				m_CleanUpdaters.push_back(cid);

			}

			void PhySimpleFollower::Update()
			{
				
			}

			void PhySimpleFollower::AddPhySprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer, Vec2Int displaySize)
			{
				m_PhySprite = new PhySprite(assetName, position, size, layer, displaySize);
				m_UsingPhySprite = true;
				ConfigureTimeEffected(m_Sprite);
			}

			PhySprite* PhySimpleFollower::GetPhySprite() const
			{
				return m_PhySprite;
			}

			void PhySimpleFollower::DestroySelf()
			{
				if (m_Sprite)
					m_Sprite->DestroySelf();

				if (m_PhySprite)
					m_PhySprite->DestroySelf();

				CleanUpdaters();
				SimpleFollower::DestroySelf();
			}
		}
	}
}