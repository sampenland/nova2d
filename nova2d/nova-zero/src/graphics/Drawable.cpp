#include "Drawable.h"
#include "../core/Game.h"
#include "../graphics/DrawableCollection.h"

namespace novazero
{
	namespace graphics
	{

		Drawable::Drawable(Vec2Int size) : m_NonScale(false), m_Layer(0), Positional()
		{
			m_ID = n2dGameGetID();
			m_Size = size;
			m_Scale = new float;
			*m_Scale = 1.f;
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
			m_Offset = Vec2((float)-GetWidth() / 2, (float)-GetHeight() / 2);
		}

		void Drawable::SetOrigin(float x, float y)
		{
			m_Offset = Vec2(x, y);
		}

		void Drawable::OriginTopLeft()
		{
			m_Offset = Vec2(0, 0);
		}
	}
}