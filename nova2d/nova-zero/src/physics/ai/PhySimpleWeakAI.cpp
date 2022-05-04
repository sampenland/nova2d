#include "PhySimpleWeakAI.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace core;

			PhySimpleWeakAI::PhySimpleWeakAI(const std::string& assetName, Vec2 position, 
				Vec2 size, unsigned char layer, Vec2Int displaySize, const std::string& colliderName)
				: SimpleWeakAI()
			{
				m_Sprite = new PhySprite(assetName, position, size, layer, displaySize, colliderName);
				m_Sprite->OriginCenter();
				LinkPositionalDrawable(m_Sprite);

				Positional::SetPosition(position);

				auto cleanID = n2dAddUpdater(PhySimpleWeakAI::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}

			void PhySimpleWeakAI::Update()
			{
				m_Sprite->SetPosition(SimpleWeakAI::Positional::GetWorldCenterPosition());
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