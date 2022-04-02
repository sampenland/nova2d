#include "BoundUser.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;

		void BoundUser::ConfigureUsingBounds(bool usesMoveBounds, bool usesAliveBounds)
		{
			m_UsingMoveBounds = usesMoveBounds;
			m_UsingAliveBounds = usesAliveBounds;
		}

		void BoundUser::ConfigureAliveBounds(Rect bounds) { m_AliveBounds = bounds; m_UsingAliveBounds = true; }
		void BoundUser::ConfigureOrigin(Origins origin)
		{
			m_Origin = origin;
		}

		void BoundUser::ConfigureMoveBounds(Rect bounds) { m_MoveBounds = bounds; m_UsingMoveBounds = true; }

		Rect BoundUser::GetMoveBounds() { return m_MoveBounds; }

		bool BoundUser::IsWithinMoveBounds(float x, float y)
		{
			if (!m_UsingMoveBounds) return true;

			return x > m_MoveBounds.x && x < m_MoveBounds.x + m_MoveBounds.w &&
				y > m_MoveBounds.y && y < m_MoveBounds.y + m_MoveBounds.h;

		}

		bool BoundUser::IsWithinMoveBounds(int x, int y, int spriteWidth, int spriteHeight)
		{
			if (!m_UsingMoveBounds) return true;

			if (spriteWidth != -1 && spriteHeight != -1 && m_Origin != Origins::TopLeft)
			{
				switch (m_Origin)
				{
				case Origins::Centered:

					int currentX = x + spriteWidth;
					int currentY = y + spriteHeight;
					
					return currentX > m_MoveBounds.x && 
						currentX < m_MoveBounds.x + m_MoveBounds.w &&
						currentY > m_MoveBounds.y && 
						currentY < m_MoveBounds.y + m_MoveBounds.h;

					break;
				}
			}

			// Top left
			return (
					(x > m_MoveBounds.x) &&
					(x < m_MoveBounds.x + m_MoveBounds.w) &&
					(y > m_MoveBounds.y) && 
					(y < m_MoveBounds.y + m_MoveBounds.h));
		}

		bool BoundUser::OutOfBounds(Drawable* drawable)
		{
			if (!m_UsingAliveBounds) return false;

			bool outOfBounds = false;
			if (drawable)
			{
				float x = drawable->GetX();
				float y = drawable->GetY();
				int w = drawable->GetWidth();
				int h = drawable->GetHeight();

				float bx = m_AliveBounds.x;
				float by = m_AliveBounds.y;
				float bw = m_AliveBounds.w;
				float bh = m_AliveBounds.h;

				return !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
			}

			return true;
		}
	}
}