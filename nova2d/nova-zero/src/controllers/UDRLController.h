#pragma once
#include "SimpleController.h"
#include <functional>
#include "../maths/Rect.h"
#include "../core/BoundUser.h"
#include "../core/TypeDefs.h"

typedef std::function<void()> f_VoidFunction;

namespace novazero
{
	namespace controllers
	{
		class UDRLController : 
			public SimpleController, 
			public BoundUser
		{

		private:

			bool m_UsingJoystick = false;
			char m_JoyStickNumber = 0;

		public:

			UDRLController(std::string spriteSheet, Vec2Int position, Vec2Int size, char layer);
			~UDRLController();

			void ConfigureMove(int moveSpeed);
			void ConfigureJoystickNumber(char num) { m_JoyStickNumber = num; }

			void EnableWASD(bool isEnabled);
			void EnableArrowKeys(bool isEnabled);
			void EnableXbox360(bool isEnabled);

			void LJoyX(float delta);
			void LJoyY(float delta);

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

			void DestroySelf();

		};
	}
}