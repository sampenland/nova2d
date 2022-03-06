#include "Drawable.h"
#include "../core/Game.h"
#include "../graphics/DrawableCollection.h"

namespace novazero
{
	namespace graphics
	{

		Drawable::Drawable() : m_Layer(0), Positional()
		{
			m_ID = n2dGameGetID();
		};

		void Drawable::SetDrawableCollection(DrawableCollection* collection)
		{
			n2dRemoveDrawable(m_ID, m_Layer);
			m_DrawableCollection = collection;
			m_DrawableCollection->AddChild(this);
		}

		void Drawable::ClearDrawableCollection(unsigned int id)
		{
			if (!m_DrawableCollection) return;
			m_DrawableCollection->RemoveChild(id);			
		}

		void Drawable::OriginCenter()
		{
			m_Offset = Vec2Int(-(GetWidth() * m_Scale) / 2, -(GetHeight() * m_Scale) / 2);
		}

		void Drawable::OriginTopLeft()
		{
			m_Offset = Vec2Int(0, 0);
		}
	}
}