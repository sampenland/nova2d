#pragma once
#include "../maths/Vec2Int.h"
#include "../maths/Vec2.h"

namespace novazero
{
	namespace graphics
	{
		class Drawable;
		class Sprite;
		class Image;
		class Text;
	}

	namespace core
	{
		using namespace maths;
		using namespace graphics;

		class Positional
		{

		private:

			Drawable* m_Drawable = nullptr;
			unsigned int m_ID;

		protected:

			Vec2Int m_Position;
			int m_Angle = 0;

		public:

			Positional();

			void LinkPositionalDrawable(Drawable* drawable);

			Sprite* GetSprite() { return (Sprite*)m_Drawable; }
			Image* GetImage() { return (Image*)m_Drawable; }
			Text* GetText() { return (Text*)m_Drawable; }

			Drawable* GetDrawable() { return m_Drawable; }

			float GetX() const;
			int* GetXRef() { return &m_Position.x; }

			float GetY() const;
			int* GetYRef() { return &m_Position.y; }

			Vec2 GetPosition() const;
			Vec2Int GetPositionInt() const;

			void SetX(float x);
			void SetY(float y);
			Vec2 GetCenter();

			void SetPosition(Vec2 position);
			void SetPositionInt(Vec2Int position);

			void SetAngle(int a);

			// Place in center screen
			void SetPositionCenter();

			// Enter values (1-100, 1-100, sprite)
			void SetPositionPercents(char xPercent, char yPercent);

		};
	}
}