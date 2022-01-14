#pragma once
#include "SimpleController.h"
#include <functional>

typedef std::function<void()> f_VoidFunction;

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

			void Configure(int moveSpeed)
			{
				m_MoveSpeed = moveSpeed;
			}

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

		};
	}
}