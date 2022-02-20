#pragma once
#include "SimpleController.h"
#include <functional>
#include "../maths/Rect.h"
#include "../core/TypeDefs.h"
#include "../physics/Graver.h"

typedef std::function<void()> f_VoidFunction;

namespace novazero
{
	namespace controllers
	{
		class UDRLController : 
			public SimpleController, 
			public Graver
		{

		private:

			char m_JoyStickNumber = 0;

		public:

			UDRLController(const std::string& spriteSheet, Vec2 position, Vec2Int size, char layer, char controllerID = 0);
			
			void ConfigureMove(float moveSpeed, TweenTypes accelerationType = TweenTypes::EaseInCubic, float accelerationMS = 0.f, float deaccelerationTimeMS = 0.f);
			void ConfigureJoystickNumber(char num) { m_JoyStickNumber = num; }

			void UpdateController();

			void AccelerateX(bool left);
			void AccelerateY(bool up);

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

			void DestroySelf();

		};
	}
}