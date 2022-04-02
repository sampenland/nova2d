#pragma once
#include "ai/SimpleWeakAI.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::ai;

		class Trees :
			public SimpleWeakAI
		{

		private:

		public:

			Trees(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

			void DestroySelf();

		};
	}
}