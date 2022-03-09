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

			void AddSprite(Drawable* sprite, BYTE layer);
			void RemoveSprite(unsigned int id, BYTE layer);
			bool HasSpriteOnLayer(Drawable* sprite, const BYTE layer);

			void ClearSprites();

			void DrawLayer(const BYTE layer) const;
			void DrawAllLayers() const;

			static unsigned int s_TotalInstances;
			static unsigned int GetInstanceCount() { return s_TotalInstances; }

		};
	}
}