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
			m_MainCamera = new Camera();

			for (int i = 0; i < MAX_LAYERS; i++)
			{
				std::vector<Drawable*> layer;
				m_Layers[i] = layer;
			}
		}

		void DrawLayers::AddSprite(Drawable* sprite, BYTE layer)
		{
			layer++;

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
				else
				{
					LOG(LVL_W, "Could not add drawable: " + tostring(sprite->m_ID));
					return;
				}
			}
		}

		bool DrawLayers::HasSpriteOnLayer(Drawable* sprite, const BYTE layer)
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

		// Does not remove sprites from 255 layer
		void DrawLayers::RemoveSprite(unsigned int id, BYTE layer)
		{
			if (layer < 0 || layer > MAX_LAYERS - 1) return;

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

		// LAYER 255 doesn't get cleared automatically
		void DrawLayers::ClearSprites()
		{
			for (int layer = 0; layer < MAX_LAYERS - 1; layer++)
			{
				m_Layers[layer].clear();
			}
			s_TotalInstances = (int)m_Layers[MAX_LAYERS - 1].size();
		}

		void DrawLayers::DrawLayer(const BYTE layer) const
		{
			for (size_t i = 0; i < (int)m_Layers[layer].size(); i++)
			{
				Vec2 camPos = m_MainCamera->GetPosition();
				m_Layers[layer][i]->Draw(camPos.x, camPos.y, CAMERA_ZOOM);
			}
		}

		void DrawLayers::DrawAllLayers() const
		{
			// Reverse draw
			for (int i = 0; i < MAX_LAYERS; i++)
			{
				DrawLayer(i);
			}
		}
	}
}