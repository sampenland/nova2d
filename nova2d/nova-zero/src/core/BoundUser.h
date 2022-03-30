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

			void ConfigureUsingBounds(bool usesMoveBounds, bool usesAliveBounds);

			void ConfigureAliveBounds(Rect bounds);
			void ConfigureOrigin(Origins origin);
				
			void ConfigureMoveBounds(Rect bounds);

			Rect GetMoveBounds();

			bool IsWithinMoveBounds(float x, float y);

			bool IsWithinMoveBounds(int x, int y, int spriteWidth = -1, int spriteHeight = -1);

			bool OutOfBounds(Drawable* drawable);

			virtual void DestroySelf() = 0;

		};
	}
}