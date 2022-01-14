#pragma once
#include <vector>
#include "../graphics/Sprite.h"
#include <cstring>

#define MAX_LAYERS 20

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

			void DrawLayer(const char layer) const;
			void DrawAllLayers() const;

		};
	}
}