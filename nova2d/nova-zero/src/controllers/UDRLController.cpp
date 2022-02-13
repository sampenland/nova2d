#include "UDRLController.h"
#include "../utils/TweenManager.h"

namespace novazero
{
	namespace controllers
	{
		using namespace input;
		using namespace utils;

		UDRLController::UDRLController(const std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			EnableWASD(true);
			EnableArrowKeys(true);
			EnableXbox360(true);

			auto cleanID = n2dAddUpdater(UDRLController::UpdateController, this);
			SimpleController::m_CleanUpdaters.push_back(cleanID);
		}

		UDRLController::~UDRLController()
		{
			EnableWASD(false);
			EnableArrowKeys(false);
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
			if (isEnabled)
			{
				// WSAD
				AddKeysEventListener(SDLK_w, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));
				AddKeysEventListener(SDLK_s, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));
				AddKeysEventListener(SDLK_d, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));
				AddKeysEventListener(SDLK_a, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));
			}
			else
			{
				// WSAD
				RemoveEventListener(SDLK_w);
				RemoveEventListener(SDLK_s);
				RemoveEventListener(SDLK_d);
				RemoveEventListener(SDLK_a);
			}
		}

		void UDRLController::EnableArrowKeys(bool isEnabled)
		{
			if (isEnabled)
			{
				// Arrow Keys
				AddKeysEventListener(SDLK_UP, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));
				AddKeysEventListener(SDLK_DOWN, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));
				AddKeysEventListener(SDLK_RIGHT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));
				AddKeysEventListener(SDLK_LEFT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));
			}
			else
			{
				// Arrow Keys
				RemoveEventListener(SDLK_UP);
				RemoveEventListener(SDLK_DOWN);
				RemoveEventListener(SDLK_RIGHT);
				RemoveEventListener(SDLK_LEFT);
			}
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
			if (delta == 32767)
			{
				MoveRight();
			}
			else if (delta == -32768)
			{
				MoveLeft();
			}
		}

		void UDRLController::LJoyY(float delta)
		{
			if (delta == 32767)
			{
				MoveDown();
			}
			else if (delta == -32768)
			{
				MoveUp();
			}
		}

		void UDRLController::UpdateController()
		{

			float timeScaleX = m_CurrentAccelerationX * n2dTimeScale * GetTimeInfluence();
			float timeScaleY = m_CurrentAccelerationY * n2dTimeScale * GetTimeInfluence();

			Vec2 pos = GetPosition();
			float newX = pos.x + (m_Velocity.x * timeScaleX);
			float newY = pos.y + (timeScaleY);

			if (IsWithinMoveBounds((int)newX, (int)pos.y))
			{
				SetX(newX);
			}

			if (IsWithinMoveBounds((int)pos.x, (int)newY))
			{
				SetY(newY);
			}

			bool yKeys = n2dIsKeyDown(SDLK_w) || n2dIsKeyDown(SDLK_s) || 
				n2dIsKeyDown(SDLK_UP) || n2dIsKeyDown(SDLK_DOWN);

			if (!yKeys)
			{
				m_AcceleratingY = false;
				n2dTweenSetDuration(m_AccelerationTweenY, m_TotalDeaccelerationSpeedMS);
				n2dTweenEnable(m_AccelerationTweenY, true, false);
			}
				
		}

		void UDRLController::AccelerateX()
		{
			if (!m_StartingX)
			{
				m_StartingX = true;
				m_StoppingX = false;

				n2dTweenReconfigure(m_AccelerationTweenX, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, false);
				n2dTweenEnable(m_AccelerationTweenX, true, true);
			}
		}

		void UDRLController::AccelerateY(bool up)
		{
			if (m_AcceleratingY)
			{
				n2dTweenEnable(m_AccelerationTweenY, false, false);
				return;
			}

			m_AcceleratingY = true;

			float start = 0.f;
			float end = m_MoveSpeed;

			if (up)
			{
				end *= -1;
			}
			else
			{
				start = m_MoveSpeed;
				end = 0.f;
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
			if (m_Velocity.x == 1) return;
			AccelerateX();
			m_Velocity.x = 1;
		}

		void UDRLController::MoveLeft()
		{
			if (m_Velocity.x == -1) return;
			AccelerateX();
			m_Velocity.x = -1;
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