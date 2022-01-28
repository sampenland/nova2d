#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace input;

		UDRLController::UDRLController(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			EnableWASD(true);
			EnableArrowKeys(true);
			EnableXbox360(true);
		}

		UDRLController::~UDRLController()
		{
			EnableWASD(false);
			EnableArrowKeys(false);
			EnableXbox360(false);
		}

		void UDRLController::ConfigureMove(int moveSpeed)
		{
			m_MoveSpeed = moveSpeed;
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

		void UDRLController::MoveUp()
		{
			Vec2Int pos = GetPosition();
			int newY = pos.y - m_MoveSpeed;

			if (IsWithinMoveBounds(pos.x, newY))
			{
				SetY(newY);
			}
		}

		void UDRLController::MoveDown()
		{
			Vec2Int pos = GetPosition();
			int newY = pos.y + m_MoveSpeed;

			if (IsWithinMoveBounds(pos.x, newY))
			{
				SetY(newY);
			}
		}

		void UDRLController::MoveRight()
		{
			Vec2Int pos = GetPosition();
			int newX = pos.x + m_MoveSpeed;

			if (IsWithinMoveBounds(newX, pos.y))
			{
				SetX(newX);
			}
		}

		void UDRLController::MoveLeft()
		{
			Vec2Int pos = GetPosition();
			int newX = pos.x - m_MoveSpeed;

			if (IsWithinMoveBounds(newX, pos.y))
			{
				SetX(newX);
			}
		}

		void UDRLController::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;

			SimpleController::CleanUpdaters();

			if (m_Sprite)
				m_Sprite->DestroySelf();

			SimpleController::SetDeleted(true);
		}
	}
}