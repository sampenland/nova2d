#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{
		UDRLController::UDRLController(const char* spriteSheet, Vec2 position, Vec2 size, char layer)
			: SimpleController(spriteSheet, position, size, layer)
		{
			AddKeysEventListener(SDLK_w, &InputHandler::IsKeyDown, std::bind(&UDRLController::MoveUp, this));			
			
			
			
			Game::AddEventStepper(std::bind(&UDRLController::EventStep, this));
		}

		UDRLController::~UDRLController()
		{

		}

		void UDRLController::MoveUp()
		{
			SetY((int)GetPosition().y - m_MoveSpeed);
		}

		void UDRLController::MoveDown()
		{
			SetY((int)GetPosition().y + m_MoveSpeed);
		}

		void UDRLController::MoveRight()
		{
			SetX((int)GetPosition().x + m_MoveSpeed);
		}

		void UDRLController::MoveLeft()
		{
			SetX((int)GetPosition().x - m_MoveSpeed);
		}
	}
}