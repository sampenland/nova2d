#include "../core/Game.h"

#include "DrawLayers.h"

namespace novazero
{
	namespace graphics
	{
		using namespace logging;

		unsigned int DrawLayers::s_TotalInstances = 0;

		DrawLayers::DrawLayers()
		{
			for (int i = 0; i < MAX_LAYERS; i++)
			{
				std::vector<Drawable*> layer;
				m_Layers[i] = layer;
			}
		}

		DrawLayers::~DrawLayers()
		{

		}

		void DrawLayers::AddSprite(Drawable* sprite, const char layer)
		{
			if (sprite)
			{
				if (layer < MAX_LAYERS)
				{
					if (!HasSpriteOnLayer(sprite, layer)) 
					{
						sprite->m_Layer = layer;
						m_Layers[layer].push_back(sprite);
						s_TotalInstances++;
					}
				}
			}
		}

		bool DrawLayers::HasSpriteOnLayer(Drawable* sprite, const char layer)
		{
			if (sprite)
			{
				if (layer < MAX_LAYERS)
				{
					return m_Layers[layer].end() != std::find(m_Layers[layer].begin(), m_Layers[layer].end(), sprite);
				}
			}

			return false;
		}

		void DrawLayers::RemoveSprite(unsigned int id, char layer)
		{
			if (layer < 0 || layer > MAX_LAYERS) return;

			int idx = -1;
			for (int i = 0; i < (int)m_Layers[layer].size(); i++)
			{
				if (m_Layers[layer][i]->m_ID == id)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1)
				return;

			m_Layers[layer].erase(m_Layers[layer].begin() + idx);
			s_TotalInstances--;
		}

		void DrawLayers::ClearSprites()
		{
			for (int layer = 0; layer < MAX_LAYERS; layer++)
			{
				m_Layers[layer].clear();
			}
			s_TotalInstances = 0;
		}

		void DrawLayers::DrawLayer(const char layer) const
		{
			for (int i = 0; i < (int)m_Layers[layer].size(); i++)
			{
				m_Layers[layer][i]->Draw();
			}
		}

		void DrawLayers::DrawAllLayers() const
		{
			// Reverse draw
			for (int i = MAX_LAYERS - 1; i >= 0; i--)
			{
				DrawLayer(i);
			}
		}
	}
}