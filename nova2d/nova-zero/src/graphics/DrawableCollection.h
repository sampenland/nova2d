#pragma once
#include "Drawable.h"
#include <map>
#include "../core/Positional.h"
#include "../core/Deleteable.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		class DrawableCollection : public Drawable, public Deleteable
		{

		private:

			std::map<unsigned int, Drawable*> m_Children;

		public:

			DrawableCollection(Vec2 pos, char layer);

			unsigned int AddChild(Drawable* child);
			void RemoveChild(unsigned int id);

			void Draw(float oX = 0.f, float oY = 0.f, float zoom = 1.f) override;
			void ClearChildren();

			void DestroySelf();

		};

	}
}