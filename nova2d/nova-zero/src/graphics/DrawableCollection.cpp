#pragma once
#include "DrawableCollection.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		DrawableCollection::DrawableCollection(Vec2 pos, char layer) : Deleteable("drawCollection_"), Drawable(Vec2Int(0,0))
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "drawCollection_" + std::to_string(m_ID);

			Positional::SetPosition(pos);

			n2dAddDrawable(this, layer);
		}

		unsigned int DrawableCollection::AddChild(Drawable* child)
		{
			auto id = n2dGameGetID();
			m_Children[id] = child;
			return id;
		}

		void DrawableCollection::RemoveChild(unsigned int id)
		{
			for (std::map<unsigned int, Drawable*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
			{
				if (it->first == id)
				{
					m_Children.erase(it);
					break;
				}
			}
		}

		void DrawableCollection::Draw(float oX, float oY, float zoom)
		{
			for (std::map<unsigned int, Drawable*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
			{
				it->second->Draw(Positional::GetX(), Positional::GetY(), zoom);
			}
		}

		void DrawableCollection::ClearChildren()
		{
			for (std::map<unsigned int, Drawable*>::iterator it = m_Children.begin(); it != m_Children.end(); it++)
			{
				n2dRemoveDrawable(it->second->m_ID, it->second->m_Layer);
			}

			m_Children.clear();
		}

		void DrawableCollection::DestroySelf()
		{
			ClearChildren();
			n2dRemoveDrawable(m_ID, m_Layer);
			CleanUpdaters();
			SetDeleted(true);
		}

	}
}