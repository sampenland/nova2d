#include "UDRLController.h"
#include "../utils/TweenManager.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace input;
		using namespace utils;
		using namespace core;

		UDRLController::UDRLController(const std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			/*EnableWASD(true);
			EnableArrowKeys(true);*/
			EnableXbox360(true);

			auto cleanID = n2dAddUpdater(UDRLController::UpdateController, this);
			SimpleController::m_CleanUpdaters.push_back(cleanID);
		}

		UDRLController::~UDRLController()
		{
			/*EnableWASD(false);
			EnableArrowKeys(false);*/
			EnableXbox360(false);
		}

		void UDRLController::ConfigureMove(float moveSpeed, 
			TweenTypes accelerationType, float accelerationMS,	
			float deaccelerationTimeMS)
		{
			SetMoveSpeed(moveSpeed);
			if (accelerationMS != 0)
			{
				SetAcceleration(accelerationType, accelerationMS, deaccelerationTimeMS);
			}
		}

		void UDRLController::EnableWASD(bool isEnabled)
		{
			//if (isEnabled)
			//{
			//	// WSAD
			//	AddKeysEventListener(SDLK_w, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));
			//	AddKeysEventListener(SDLK_s, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));
			//	AddKeysEventListener(SDLK_d, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));
			//	AddKeysEventListener(SDLK_a, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));
			//}
			//else
			//{
			//	// WSAD
			//	RemoveEventListener(SDLK_w);
			//	RemoveEventListener(SDLK_s);
			//	RemoveEventListener(SDLK_d);
			//	RemoveEventListener(SDLK_a);
			//}
		}

		void UDRLController::EnableArrowKeys(bool isEnabled)
		{
			//if (isEnabled)
			//{
			//	// Arrow Keys
			//	AddKeysEventListener(SDLK_UP, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));
			//	AddKeysEventListener(SDLK_DOWN, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));
			//	AddKeysEventListener(SDLK_RIGHT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));
			//	AddKeysEventListener(SDLK_LEFT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));
			//}
			//else
			//{
			//	// Arrow Keys
			//	RemoveEventListener(SDLK_UP);
			//	RemoveEventListener(SDLK_DOWN);
			//	RemoveEventListener(SDLK_RIGHT);
			//	RemoveEventListener(SDLK_LEFT);
			//}
		}

		void UDRLController::EnableXbox360(bool isEnabled)
		{
			if (isEnabled)
			{
				AddJoyAxisEventListener(m_JoyStickNumber, JOY_STICK_AXIS_X,
					&InputHandler::GetJoystickAxis,
					std::bind(&UDRLController::LJoyX, this, std::placeholders::_1));
				
				AddJoyAxisEventListener(m_JoyStickNumber, JOY_STICK_AXIS_Y,
					&InputHandler::GetJoystickAxis,
					std::bind(&UDRLController::LJoyY, this, std::placeholders::_1));
			}
			else
			{
				RemoveJoyAxisEventListener(m_JoyStickNumber);
			}
		}

		void UDRLController::LJoyX(float delta)
		{
			if (delta == 32767 || delta == -32768)
			{
				AccelerateX(delta == -32768);
				m_JoyX = true;
			}
			else
			{
				m_JoyX = false;
			}
		}

		void UDRLController::LJoyY(float delta)
		{
			if (delta == 32767 || delta == -32768)
			{
				AccelerateY(delta == -32768);
				m_JoyY = true;
			}
			else
			{
				m_JoyY = false;
			}
		}

		void UDRLController::UpdateController()
		{
			bool pX = n2dIsKeyDown(SDLK_RIGHT);
			bool nX = n2dIsKeyDown(SDLK_LEFT);

			bool pY = n2dIsKeyDown(SDLK_DOWN);
			bool nY = n2dIsKeyDown(SDLK_UP);

			float accelX = m_CurrentAccelerationX;
			float accelY = m_CurrentAccelerationY;

			if (accelX > 0.f && accelX < 1.f) accelX = 1.f;
			if (accelY > 0.f && accelY < 1.f) accelY = 1.f;

			float timeScaleX = accelX * n2dTimeScale * GetTimeInfluence();
			float timeScaleY = accelY * n2dTimeScale * GetTimeInfluence();

			if (timeScaleX == 0.f)
			{
				m_DeacceleratingX = false;
			}

			if (timeScaleY == 0.f)
			{
				m_DeacceleratingY = false;
			}

			if (!pX && !nX)
			{
				m_AcceleratingX = false;
			}
			else if (pX && accelX < 0.f)
			{
				m_AcceleratingX = false;
			}
			else if (nX && accelX > 0.f)
			{
				m_AcceleratingX = false;
			}

			if (!pY && !nY)
			{
				m_AcceleratingY = false;
			}
			else if (pY && accelY < 0.f)
			{
				m_AcceleratingY = false;
			}
			else if (nY && accelY > 0.f)
			{
				m_AcceleratingY = false;
			}

			Vec2 pos = GetPosition();
			float newX = pos.x + (timeScaleX); // fix int casting ROUND downwards to 0 speed issue
			float newY = pos.y + (timeScaleY); // fix int casting ROUND downwards to 0 speed issue

			if (pos != Vec2(newX, newY))
			{
				if (IsWithinMoveBounds((int)newX, (int)pos.y))
				{
					SetX(newX);
				}

				if (IsWithinMoveBounds((int)pos.x, (int)newY))
				{
					SetY(newY);
				}
			}

			if (nX)
			{
				AccelerateX(true);
			}
			
			if (pX)
			{
				AccelerateX(false);
			}

			if (nY)
			{
				AccelerateY(true);
			}

			if (pY)
			{
				AccelerateY(false);
			}

			bool stopX = (!pX && !nX) || (!pX && m_CurrentAccelerationX > 0.f) || (!nX && m_CurrentAccelerationX < 0.f);
			if (stopX && !m_DeacceleratingX && m_CurrentAccelerationX != 0.f)
			{
				m_DeacceleratingX = true;
				n2dTweenReconfigure(m_AccelerationTweenX, m_CurrentAccelerationX, 0.f, m_TotalDeaccelerationSpeedMS, false, false);
				n2dTweenEnable(m_AccelerationTweenX, true, false);
			}

			bool stopY = (!pY && !nY) || (!pY && m_CurrentAccelerationY > 0.f) || (!nY && m_CurrentAccelerationY < 0.f);
			if (stopY && !m_DeacceleratingY && m_CurrentAccelerationY != 0.f)
			{
				m_DeacceleratingY = true;
				n2dTweenReconfigure(m_AccelerationTweenY, m_CurrentAccelerationY, 0.f, m_TotalDeaccelerationSpeedMS, false, false);
				n2dTweenEnable(m_AccelerationTweenY, true, false);
			}
				
		}

		void UDRLController::AccelerateX(bool left)
		{
			if (m_AcceleratingX)
			{
				return;
			}

			m_AcceleratingX = true;

			float start = 0.f;
			float end = m_MoveSpeed;

			if (left)
			{
				end *= -1;
			}

			n2dTweenReconfigure(m_AccelerationTweenX, start, end, m_TotalAccelerationSpeedMS, false, false);
			n2dTweenEnable(m_AccelerationTweenX, true, true);
		}

		void UDRLController::AccelerateY(bool up)
		{
			if (m_AcceleratingY)
			{
				return;
			}

			m_AcceleratingY = true;

			float start = 0.f;
			float end = m_MoveSpeed;

			if (up)
			{
				end *= -1;
			}

			n2dTweenReconfigure(m_AccelerationTweenY, start, end, m_TotalAccelerationSpeedMS, false, false);
			n2dTweenEnable(m_AccelerationTweenY, true, true);
		}

		void UDRLController::MoveUp()
		{
			AccelerateY(true);
		}

		void UDRLController::MoveDown()
		{
			AccelerateY(false);
		}

		void UDRLController::MoveRight()
		{
			AccelerateX(false);
		}

		void UDRLController::MoveLeft()
		{
			AccelerateX(true);
		}

		void UDRLController::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;

			SimpleController::CleanUpdaters();
			SimpleController::DestroySelf();

			if (m_Sprite)
				m_Sprite->DestroySelf();

			SimpleController::SetDeleted(true);
		}

	}
}