#pragma once
#include "../maths/Vec2Int.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace graphics
	{
		class Drawable;
		class Sprite;
	}

	namespace core
	{
		using namespace maths;
		using namespace graphics;

		class Positional
		{

		protected:
			
			Vec2 m_Position;
			int m_Angle = 0;
			Vec2Int m_Size;
			Sprite* m_Sprite = nullptr;

		public:

			Positional();

			void LinkPositionalSprite(Sprite* sprite);
			Sprite* GetLinkedSprite() { return m_Sprite; }

			float GetX() const;
			float* GetXRef() { return &m_Position.x; }
			float GetY() const;
			float* GetYRef() { return &m_Position.y; }
			Vec2 GetPosition() const;
			Vec2Int GetPositionInt() const;

			int GetWidth() const;
			int GetHeight() const;
			Vec2Int GetSize() const;
			Vec2 GetCenter() const;

			int GetAngle() const;

			void SetX(float x);
			
			void SetY(float y);

			void SetPosition(Vec2 position);
			void SetPositionInt(Vec2Int position);

			void SetSize(Vec2Int size);

			void SetAngle(int a);

			// Place in center screen
			void SetPositionCenter();

			// Enter values (1-100, 1-100, sprite)
			void SetPositionPercents(char xPercent, char yPercent);

		};
	}
}