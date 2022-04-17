#include "PhySimpleWeakAI.h"
#include "../../core/Game.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace core;

			PhySimpleWeakAI::PhySimpleWeakAI(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer, Vec2Int displaySize)
				: SimpleWeakAI()
			{
				m_Sprite = new PhySprite(assetName, position, size, layer, displaySize);
				LinkPositionalDrawable(m_Sprite);

				auto cleanID = n2dAddUpdater(PhySimpleWeakAI::Update, this);
				m_CleanUpdaters.push_back(cleanID);
			}

			void PhySimpleWeakAI::Update()
			{
				m_Sprite->SetPosition(SimpleWeakAI::Positional::GetPosition());
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