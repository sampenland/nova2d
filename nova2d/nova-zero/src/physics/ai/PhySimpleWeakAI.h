#pragma once
#include "../../ai/SimpleWeakAI.h"
#include "../PhySprite.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace novazero::ai;

			class PhySimpleWeakAI
				: public SimpleWeakAI
			{
			private:

				PhySprite* m_Sprite = nullptr;

			public:

				PhySimpleWeakAI(const std::string& assetName, Vec2 position, Vec2 size, 
					unsigned char layer, Vec2Int displaySize, const std::string& colliderName);

				void Update();

				PhySprite* GetPhysicsSprite() const;

				void DestroySelf();

			};
		}
	}
}