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

			UDRLController(std::string spriteSheet, Vec2Int position, Vec2Int size, char layer);
			~UDRLController();

			void ConfigureMove(int moveSpeed, maths::Rect moveBounds);
			inline void EnableBounds(bool enableBounds) { m_UsingBounds = enableBounds; }

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

		};
	}
}