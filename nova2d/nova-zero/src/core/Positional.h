#pragma once
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace graphics
	{
		class Drawable;
	}

	namespace core
	{
		using namespace maths;
		using namespace graphics;

		class Positional
		{

		protected:
			
			Vec2Int m_Position;
			int m_Angle = 0;
			Vec2Int m_Size;

		public:

			Positional();
			~Positional();

			int GetX() const;
			int GetY() const;
			Vec2Int GetPosition() const;

			int GetWidth() const;
			int GetHeight() const;
			Vec2Int GetSize() const;
			Vec2Int GetCenter() const;

			int GetAngle() const;

			void SetX(int x);
			
			void SetY(int y);

			void SetPosition(Vec2Int position);

			void SetSize(Vec2Int size);

			void SetAngle(int a);

			// Place in center screen
			void SetPositionCenter();

			// Enter values (1-100, 1-100, sprite)
			void SetPositionPercents(char xPercent, char yPercent);

		};
	}
}