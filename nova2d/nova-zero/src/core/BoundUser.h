#pragma once
#include "../graphics/Sprite.h"
#include "../maths/Rect.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;

		class BoundUser
		{
		
		protected:
		
			BoundUser() : m_AliveBounds(Rect(0,0,0,0)) { };
		
		public:

			Rect m_AliveBounds;
			bool m_Alive = true;

			void SetAliveBounds(Rect bounds) { m_AliveBounds = bounds; }

			void OutOfBounds(Sprite* sprite, Rect bounds)
			{
				if (!m_Alive) return;

				if (sprite)
				{
					int x = sprite->GetX();
					int y = sprite->GetY();
					int w = sprite->GetWidth();
					int h = sprite->GetHeight();

					int bx = bounds.x;
					int by = bounds.y;
					int bw = bounds.w;
					int bh = bounds.h;

					m_Alive = !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
					return;
				}

				m_Alive = true;
			}
		};
	}
}