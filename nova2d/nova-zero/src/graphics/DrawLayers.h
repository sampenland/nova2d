#pragma once
#include "../core/Defines.h"
#include <vector>
#include "../graphics/Sprite.h"
#include <cstring>
#include "../logging/logging.h"

namespace novazero
{
	namespace graphics
	{
		class DrawLayers
		{

		private:

			std::vector<Sprite*> m_Layers[MAX_LAYERS];

		public:

			DrawLayers();
			~DrawLayers();

			void AddSprite(Sprite* sprite, const char layer);
			void RemoveSprite(unsigned int id, char layer);

			void ClearSprites();

			void DrawLayer(const char layer) const;
			void DrawAllLayers() const;

		};
	}
}