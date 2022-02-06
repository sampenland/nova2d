#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace input;

		UDRLController::UDRLController(std::string assetName, Vec2 position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			EnableWASD(true);
			EnableArrowKeys(true);
			EnableXbox360(true);

			auto cleanID = n2dAddUpdater(UDRLController::ResetAccelerationCheck, this);
			SimpleController::m_CleanUpdaters.push_back(cleanID);
		}

		UDRLController::~UDRLController()
		{
			EnableWASD(false);
			EnableArrowKeys(false);
			EnableXbox360(false);
		}

		void UDRLController::ConfigureMove(float moveSpeed, float timeToMaxMoveSpeed)
		{
			SetMoveSpeed(moveSpeed);
			if (timeToMaxMoveSpeed != 0)
			{
				SetAcceleration(AccelerationTypes::Linear, timeToMaxMoveSpeed);
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

		void UDRLController::Accelerate()
		{
			if (!m_Starting)
			{
				m_Starting = true;
				m_Stopping = false;
				n2dTweenReconfigure(m_AccelerationTween, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, false);
				n2dTweenEnable(m_AccelerationTween, true, true);
			}
		}

		void UDRLController::MoveUp()
		{
			Vec2 pos = GetPosition();
			float newY = pos.y - (m_CurrentSpeed * n2dTimeScale * GetTimeInfluence());

			if (IsWithinMoveBounds((int)pos.x, (int)newY))
			{
				Accelerate();
				SetY(newY);
			}
		}

		void UDRLController::MoveDown()
		{
			Vec2 pos = GetPosition();
			float newY = pos.y + (m_CurrentSpeed * n2dTimeScale * GetTimeInfluence());

			if (newY - (int)newY > 0) newY = ceil(newY);

			if (IsWithinMoveBounds((int)pos.x, (int)newY))
			{
				Accelerate();
				SetY(newY);
			}
		}

		void UDRLController::MoveRight()
		{
			Vec2 pos = GetPosition();
			float newX = pos.x + (m_CurrentSpeed * n2dTimeScale * GetTimeInfluence());

			if (newX - (int)newX > 0) newX = ceil(newX);

			if (IsWithinMoveBounds((int)newX, (int)pos.y))
			{
				Accelerate();
				SetX(newX);
			}
		}

		void UDRLController::MoveLeft()
		{
			Vec2 pos = GetPosition();
			float newX = pos.x - (m_CurrentSpeed * n2dTimeScale * GetTimeInfluence());

			if (IsWithinMoveBounds((int)newX, (int)pos.y))
			{
				Accelerate();
				SetX(newX);
			}
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
					Game::s_InputHandler->IsKeyUp(SDLK_w) &&
					Game::s_InputHandler->IsKeyUp(SDLK_a) &&
					Game::s_InputHandler->IsKeyUp(SDLK_s) &&
					Game::s_InputHandler->IsKeyUp(SDLK_d) &&
					Game::s_InputHandler->IsKeyUp(SDLK_UP) &&
					Game::s_InputHandler->IsKeyUp(SDLK_DOWN) &&
					Game::s_InputHandler->IsKeyUp(SDLK_RIGHT) &&
					Game::s_InputHandler->IsKeyUp(SDLK_LEFT)
					)
				{
					if (m_Starting)
					{
						m_Starting = false;
						MovementIsZero();
					}
				}
			}
		}
	}
}