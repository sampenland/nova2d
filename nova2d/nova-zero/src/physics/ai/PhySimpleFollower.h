#pragma once
#include "../../ai/SimpleFollower.h"
#include "../../physics/PhySprite.h"

namespace novazero
{
	namespace physics
	{
		namespace ai
		{
			using namespace novazero::ai;

			class PhySimpleFollower :
				public SimpleFollower
			{

			private:

				PhySprite* m_Sprite = nullptr;

			public:

				PhySimpleFollower(Positional* target, float moveDelay);

				void AddPhySprite(const std::string& assetName, Vec2 position, Vec2 size, 
					unsigned char layer, Vec2Int displaySize, const std::string& colliderName);
				PhySprite* GetPhySprite() const;

				void Update();

				void DestroySelf();
			};
		}

	}
}