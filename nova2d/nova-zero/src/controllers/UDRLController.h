#pragma once
#include "SimpleController.h"
#include <functional>

namespace novazero
{
	namespace controllers
	{
		class UDRLController
			: public SimpleController
		{

		private:

		public:

			UDRLController(const char* spriteSheet, Vec2 position, Vec2 size, char layer);
			~UDRLController();

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

		};
	}
}