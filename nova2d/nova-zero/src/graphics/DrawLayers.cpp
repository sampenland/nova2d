#include "DrawLayers.h"

namespace novazero
{
	namespace graphics
	{
		DrawLayers::DrawLayers()
		{
			for (int i = 0; i < MAX_LAYERS; i++)
			{
				std::vector<Sprite*> layer;
				m_Layers[i] = layer;
			}
		}

		DrawLayers::~DrawLayers()
		{

		}

		void DrawLayers::AddSprite(Sprite* sprite, const char layer)
		{
			if (sprite)
			{
				if (layer < MAX_LAYERS)
				{
					m_Layers[layer].push_back(sprite);
				}
			}
		}

		void DrawLayers::DrawLayer(const char layer) const
		{
			for (int i = 0; i < m_Layers[layer].size(); i++)
			{
				m_Layers[layer][i]->Draw();
			}
		}

		void DrawLayers::DrawAllLayers() const
		{
			for (int i = 0; i < MAX_LAYERS; i++)
			{
				DrawLayer(i);
			}
		}
	}
}