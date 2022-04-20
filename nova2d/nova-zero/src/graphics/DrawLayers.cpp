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

			for (int i = 0; i < MAX_LAYERS + 1; i++)
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
				if (layer <= MAX_LAYERS)
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
					LOG(LVL_W, "Could not add drawable: " + tostring(sprite->m_ID), __FILE__, __LINE__);
					return;
				}
			}
		}

		bool DrawLayers::HasSpriteOnLayer(Drawable* sprite, const BYTE layer)
		{
			if (sprite)
			{
				if (layer <= MAX_LAYERS)
				{
					return m_Layers[layer].end() != std::find(m_Layers[layer].begin(), m_Layers[layer].end(), sprite);
				}
			}

			return false;
		}

		// Does not remove sprites from 255 layer
		void DrawLayers::RemoveSprite(unsigned int id, BYTE layer)
		{
			if (layer == PERSISTENT_LAYER) return;

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
				if (layer == PERSISTENT_LAYER) continue;
				m_Layers[layer].clear();
			}
			s_TotalInstances = (int)m_Layers[PERSISTENT_LAYER].size();
		}

		void DrawLayers::DrawLayer(const BYTE layer) const
		{
			Rect cameraDrawArea = CAMERA_RECT;
			
			for (size_t i = 0; i < (int)m_Layers[layer].size(); i++)
			{
				Drawable& drawable = *m_Layers[layer][i];

				Vec2 drawablePos = drawable.GetPosition();
				Vec2Int drawableSize = drawable.GetSize();
				
				// CULL:: DO NOT DRAW (outside of camera space) if needed
				if (

					// left culling
					drawablePos.x + drawableSize.x < -cameraDrawArea.x || 

					// right culling
					(cameraDrawArea.x < cameraDrawArea.w ? (drawablePos.x > cameraDrawArea.x + cameraDrawArea.w) :
						drawablePos.x > cameraDrawArea.x) ||

					// top culling
					drawablePos.y + drawableSize.y < -cameraDrawArea.y ||

					// bottom culling
					(cameraDrawArea.y < cameraDrawArea.h ? (drawablePos.y > cameraDrawArea.y + cameraDrawArea.h) :
						drawablePos.y > cameraDrawArea.y)

					)
				{
					if (!drawable.IsNotScaleable())
					{
						continue;
					}
				}				
				
				float zoom = CAMERA_ZOOM;

				if (drawable.IsNotScaleable())
				{
					zoom = 1.f;
				}

				float x = (drawablePos.x * zoom) - cameraDrawArea.x;
				float y = (drawablePos.y * zoom) - cameraDrawArea.y;

				drawable.Draw(x, y, zoom);
			}
		}

		void DrawLayers::DrawAllLayers() const
		{
			// Reverse draw
			for (int i = 0; i <= MAX_LAYERS; i++)
			{
				DrawLayer(i);
			}
		}
	}
}