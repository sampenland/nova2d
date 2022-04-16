#include "PhySimpleWeakAI.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace core;

			PhySimpleWeakAI::PhySimpleWeakAI(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
				: SimpleWeakAI()
			{
				m_Sprite = new PhySprite(assetName, position, size, layer);
				LinkPositionalDrawable(m_Sprite);

				auto cleanID = n2dAddUpdater(PhySimpleWeakAI::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}

			void PhySimpleWeakAI::Update()
			{
				LOGS(m_Sprite->GetPosition());
			}

			PhySprite* PhySimpleWeakAI::GetPhysicsSprite() const
			{
				return m_Sprite;
			}

			void PhySimpleWeakAI::DestroySelf()
			{
				CleanUpdaters();
				SimpleWeakAI::DestroySelf();
			}
		}
	}
}