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

		private:

			bool m_UsingMoveBounds = false;
			bool m_UsingAliveBounds = false;
		
		protected:
		
			BoundUser() : m_AliveBounds(Rect(0,0,0,0)), m_MoveBounds(Rect(0,0,0,0)) { };
		
		public:

			Rect m_AliveBounds;
			Rect m_MoveBounds;

			bool m_Alive = true;

			void SetUsingBounds(bool usesMoveBounds, bool usesAliveBounds) 
			{	
				m_UsingMoveBounds = usesMoveBounds;
				m_UsingAliveBounds = usesAliveBounds;
			}

			void ConfigureAliveBounds(Rect bounds) { m_AliveBounds = bounds; m_UsingAliveBounds = true; }
			void SetMoveBounds(Rect bounds) { m_MoveBounds = bounds; m_UsingMoveBounds = true; }

			bool IsWithinMoveBounds(int x, int y)
			{
				if (!m_UsingMoveBounds) return true;

				return x > m_MoveBounds.x && x < m_MoveBounds.x + m_MoveBounds.w &&
					y > m_MoveBounds.y && y < m_MoveBounds.y + m_MoveBounds.h;
			}

			void OutOfBounds(Sprite* sprite)
			{
				if (!m_UsingAliveBounds) return;

				if (!m_Alive) return;

				if (sprite)
				{
					int x = sprite->GetX();
					int y = sprite->GetY();
					int w = sprite->GetWidth();
					int h = sprite->GetHeight();

					int bx = m_AliveBounds.x;
					int by = m_AliveBounds.y;
					int bw = m_AliveBounds.w;
					int bh = m_AliveBounds.h;

					m_Alive = !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
					return;
				}

				m_Alive = true;
			}

			bool m_Destroyed = false;

			bool CheckAlive()
			{
				if (!m_Alive)
				{
					if (!m_Destroyed)
					{
						DestroySelf();
					}
					return false;
				}

				return m_Alive;
			}

			virtual void DestroySelf() = 0;

		};
	}
}