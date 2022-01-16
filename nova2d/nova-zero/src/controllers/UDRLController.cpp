#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{

		UDRLController::UDRLController(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer)
		{
			// WSAD
			AddKeysEventListener(SDLK_w, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));			
			AddKeysEventListener(SDLK_s, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));			
			AddKeysEventListener(SDLK_d, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));			
			AddKeysEventListener(SDLK_a, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));	
			
			// Arrow Keys
			AddKeysEventListener(SDLK_UP, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));
			AddKeysEventListener(SDLK_DOWN, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveDown, this));
			AddKeysEventListener(SDLK_RIGHT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveRight, this));
			AddKeysEventListener(SDLK_LEFT, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveLeft, this));

			// Link so events get triggered
			Game::AddEventStepper(std::bind(&UDRLController::EventStep, this));
		}

		UDRLController::~UDRLController()
		{
			Game::RemoveEventStepper(std::bind(&UDRLController::EventStep, this));
		}

		void UDRLController::ConfigureMove(int moveSpeed)
		{
			m_MoveSpeed = moveSpeed;
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

			Game::RemoveEventStepper(std::bind(&UDRLController::EventStep, this));

			if (m_Sprite)
				delete m_Sprite;
		}
	}
}