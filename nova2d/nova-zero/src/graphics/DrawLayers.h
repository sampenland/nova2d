#pragma once
#include "../core/Defines.h"
#include <vector>
#include "Sprite.h"
#include <cstring>
#include "../logging/logging.h"
#include "Drawable.h"

namespace novazero
{
	namespace graphics
	{
		class DrawLayers
		{

		private:

			std::vector<Drawable*> m_Layers[MAX_LAYERS];

		public:

			DrawLayers();
			~DrawLayers();

			void AddSprite(Drawable* sprite, const char layer);
			void RemoveSprite(unsigned int id, char layer);
			bool HasSpriteOnLayer(Drawable* sprite, const char layer);

			void ClearSprites();

			void DrawLayer(const char layer) const;
			void DrawAllLayers() const;

		};
	}
}