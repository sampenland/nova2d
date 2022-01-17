#pragma once
#include <vector>
#include "../graphics/Sprite.h"
#include <cstring>
#include "../logging/logging.h"
#include "../core/Common.h"

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

			void DrawLayer(const char layer) const;
			void DrawAllLayers() const;

		};
	}
}