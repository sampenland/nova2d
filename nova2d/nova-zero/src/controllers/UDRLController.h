#pragma once
#include "SimpleController.h"
#include <functional>
#include "../maths/Rect.h"
#include "../physics/Graver.h"

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
			Vec2Int m_MoveOffsets = Vec2Int(0, 0);

		public:

			UDRLController(const std::string& spriteSheet, Vec2 position, Vec2Int size, unsigned char layer, char controllerID = 0);
			
			void ConfigureMove(float moveSpeed, TweenTypes accelerationType = TweenTypes::EaseInCubic, float accelerationMS = 0.f, float deaccelerationTimeMS = 0.f);
			void ConfigureJoystickNumber(char num) { m_JoyStickNumber = num; }
			void ConfigureMoveOffsets(Origins origin, int w, int h)
			{
				ConfigureOrigin(origin);
				m_MoveOffsets = Vec2Int(w, h);
			}
			void ConfigureMoveOffsets(Origins origin, Sprite* sprite)
			{
				ConfigureOrigin(origin);
				m_MoveOffsets = Vec2Int((int)(sprite->GetWidth() / 2), (int)(sprite->GetHeight() / 2));
			}

			void UpdateController();

			virtual void Update() = 0;

			void AccelerateX(bool left);
			void AccelerateY(bool up);

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

			void SetX(float x);
			void SetY(float y);

			void DestroySelf();

		};
	}
}