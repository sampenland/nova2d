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

	namespace physics
	{
		class PhySprite;
	}

	namespace core
	{
		using namespace maths;
		using namespace graphics;
		using namespace physics;

		enum class Directions
		{
			Up,
			Down,
			Right,
			Left,
			None
		};

		class Positional
		{

		private:

			Drawable* m_Drawable = nullptr;
			unsigned int m_CleanID = 0;
			Directions m_Facing = Directions::Right;

		protected:

			Vec2 m_Position;
			Vec2 m_Offset = Vec2(0, 0);
			float m_Angle = 0;
			float m_OldZoom = 1.f;

		public:

			unsigned int m_ID;

			Positional();

			void LinkPositionalDrawable(Drawable* drawable);

			Sprite* GetSprite();
			PhySprite* GetPhySprite();

			Image* GetImage() { return (Image*)m_Drawable; }
			Text* GetText() { return (Text*)m_Drawable; }

			Drawable* GetDrawable() { return m_Drawable; }

			void SetFacing(Directions facing);
			Directions IsFacing() const { return m_Facing; }

			float GetX() const;
			float* GetXRef() { return &m_Position.x; }

			float GetY() const;
			float* GetYRef() { return &m_Position.y; }

			Vec2 GetPosition() const;
			Vec2Int GetPositionInt() const;

			void SetX(float x);
			void SetY(float y);
			Vec2 GetWorldCenterPosition();
			Vec2 GetBottomRight();

			float OffsetX() { return m_Offset.x; }
			float OffsetY() { return m_Offset.y; }

			void SetOffsetX(float offsetX) { m_Offset.x = offsetX; }
			void SetOffsetY(float offsetY) { m_Offset.y = offsetY; }
			void SetOffset(Vec2 vec) { SetOffsetX(vec.x); SetOffsetY(vec.y); }

			void SetPosition(Vec2 position);
			void SetPositionInt(Vec2Int position);

			void SetAngle(float a);

			// Place in center screen
			void SetPositionCenter();

			// Enter values (1-100, 1-100, sprite)
			void SetPositionPercents(char xPercent, char yPercent);

		};
	}
}