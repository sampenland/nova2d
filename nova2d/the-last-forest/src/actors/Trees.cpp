#include "Trees.h"
#include "core/Game.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::core;
		using namespace novazero::maths;

		Trees::Trees(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		{
			
			AddSprite(assetName, position, size, layer);
			ConfigureCollider(GetSprite(), 0, "ptree");			
		}

		void Trees::DestroySelf()
		{
			SimpleWeakAI::DestroySelf();
		}
	}
}