#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace input;

		UDRLController::UDRLController(const std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			EnableWASD(true);
			EnableArrowKeys(true);
			EnableXbox360(true);

			auto cleanID = n2dAddUpdater(UDRLController::ResetAccelerationCheck, this);
			SimpleController::m_CleanUpdaters.push_back(cleanID);

			cleanID = n2dAddUpdater(UDRLController::UpdateController, this);
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
			if (m_Velocity == Vec2(0.f, 0.f)) return;

			m_Velocity.x *= (m_CurrentAccelerationX * n2dTimeScale * GetTimeInfluence());
			m_Velocity.y *= (m_CurrentAccelerationY * n2dTimeScale * GetTimeInfluence());

			Vec2 pos = GetPosition();
			float newX = pos.x + m_Velocity.x;
			float newY = pos.y + m_Velocity.y;

			if (m_Velocity.x > 0) newX = ceil(newX);
			if (m_Velocity.y > 0) newY = ceil(newY);

			if (IsWithinMoveBounds((int)newX, (int)pos.y))
			{
				SetX(newX);
			}

			if (IsWithinMoveBounds((int)pos.x, (int)newY))
			{
				SetY(newY);
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

		void UDRLController::AccelerateY()
		{
			if (!m_StartingY)
			{
				m_StartingY = true;
				m_StoppingY = false;

				n2dTweenReconfigure(m_AccelerationTweenY, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, false);
				n2dTweenEnable(m_AccelerationTweenY, true, true);
			}
		}

		void UDRLController::MoveUp()
		{
			if (m_Velocity.y == -1) return;
			AccelerateY();
			m_Velocity.y = -1;
			m_Moving.y = 1;
		}

		void UDRLController::MoveDown()
		{
			if (m_Velocity.y == 1) return;
			AccelerateY();
			m_Velocity.y = 1;
			m_Moving.y = 1;
		}

		void UDRLController::MoveRight()
		{
			if (m_Velocity.x == 1) return;
			AccelerateX();
			m_Velocity.x = 1;
			m_Moving.x = 1;
		}

		void UDRLController::MoveLeft()
		{
			if (m_Velocity.x == -1) return;
			AccelerateX();
			m_Velocity.x = -1;
			m_Moving.x = 1;
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

		void UDRLController::ResetAccelerationCheck()
		{
			if (IsUsingAcceleration())
			{
				if (
					Game::s_InputHandler->IsKeyUp(SDLK_a) &&
					Game::s_InputHandler->IsKeyUp(SDLK_d) &&
					Game::s_InputHandler->IsKeyUp(SDLK_RIGHT) &&
					Game::s_InputHandler->IsKeyUp(SDLK_LEFT)
					)
				{
					if (m_StartingX)
					{
						m_StartingX = false;
						m_StoppingX = true;
						MovementIsZeroX();
					}
				}

				if (
					Game::s_InputHandler->IsKeyUp(SDLK_w) &&
					Game::s_InputHandler->IsKeyUp(SDLK_s) &&
					Game::s_InputHandler->IsKeyUp(SDLK_UP) &&
					Game::s_InputHandler->IsKeyUp(SDLK_DOWN)
					)
				{
					if (m_StartingY)
					{
						m_StartingY = false;
						m_StoppingY = true;
						MovementIsZeroY();
					}
				}
			}
		}
	}
}