#pragma once
#include "../graphics/Sprite.h"
#include "../maths/Rect.h"

namespace novazero
{
	namespace core
	{
		using namespace graphics;
		using namespace maths;

		enum class Origins
		{
			TopLeft,
			Centered
		};

		class BoundUser
		{

		private:

			Origins m_Origin = Origins::TopLeft;
		
		protected:
		
			BoundUser() : m_AliveBounds(Rect(0,0,0,0)), m_MoveBounds(Rect(0,0,0,0)) { };
		
		public:

			Rect m_AliveBounds;
			Rect m_MoveBounds;

			bool m_UsingMoveBounds = false;
			bool m_UsingAliveBounds = false;

			bool m_Alive = true;
			bool m_Destroyed = false;

			void ConfigureUsingBounds(bool usesMoveBounds, bool usesAliveBounds) 
			{	
				m_UsingMoveBounds = usesMoveBounds;
				m_UsingAliveBounds = usesAliveBounds;
			}

			void ConfigureAliveBounds(Rect bounds) { m_AliveBounds = bounds; m_UsingAliveBounds = true; }
			void ConfigureOrigin(Origins origin)
			{
				m_Origin = origin;
			}
				
			void SetMoveBounds(Rect bounds) { m_MoveBounds = bounds; m_UsingMoveBounds = true; }

			bool IsWithinMoveBounds(int x, int y, int spriteWidth = -1, int spriteHeight = -1)
			{
				if (!m_UsingMoveBounds) return true;

				if (spriteWidth != -1 && spriteHeight != -1 && m_Origin != Origins::TopLeft)
				{
					switch (m_Origin)
					{
					case Origins::Centered:

						return x + spriteWidth > m_MoveBounds.x && x + spriteWidth < m_MoveBounds.x + m_MoveBounds.w &&
							y + spriteHeight > m_MoveBounds.y && y + spriteHeight < m_MoveBounds.y + m_MoveBounds.h;

						break;
					}
				}

				// Top left
				return x > m_MoveBounds.x && x < m_MoveBounds.x + m_MoveBounds.w &&
					y > m_MoveBounds.y && y < m_MoveBounds.y + m_MoveBounds.h;
			}

			bool OutOfBounds(Sprite* sprite)
			{
				if (!m_UsingAliveBounds) return false;

				bool outOfBounds = false;
				if (sprite)
				{
					float x = sprite->GetX();
					float y = sprite->GetY();
					int w = sprite->GetWidth();
					int h = sprite->GetHeight();

					float bx = m_AliveBounds.x;
					float by = m_AliveBounds.y;
					float bw = m_AliveBounds.w;
					float bh = m_AliveBounds.h;

					return !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
				}

				return true;
			}

			virtual void DestroySelf() = 0;

		};
	}
}