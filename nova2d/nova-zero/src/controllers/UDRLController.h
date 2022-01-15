#pragma once
#include "SimpleController.h"
#include <functional>
#include "../maths/Rect.h"

typedef std::function<void()> f_VoidFunction;

namespace novazero
{
	namespace controllers
	{
		class UDRLController
			: public SimpleController
		{

		private:

			Rect m_BoundsRect;
			bool m_UsingBounds = false;

		public:

			UDRLController(const char* spriteSheet, Vec2 position, Vec2 size, char layer);
			~UDRLController();

			void ConfigureMove(int moveSpeed, maths::Rect moveBounds);
			void EnableBounds(bool val)
			{
				m_UsingBounds = val;
			}

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

		};
	}
}