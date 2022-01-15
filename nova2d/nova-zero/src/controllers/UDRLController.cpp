#include "UDRLController.h"

namespace novazero
{
	namespace controllers
	{

		UDRLController::UDRLController(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: SimpleController(assetName, position, size, layer), m_BoundsRect(Rect(0,0,0,0)),
			m_UsingBounds(false)
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

		void UDRLController::ConfigureMove(int moveSpeed, Rect moveBounds)
		{
			m_MoveSpeed = moveSpeed;
			m_BoundsRect = moveBounds;
		}

		void UDRLController::MoveUp()
		{
			int delta = (int)GetPosition().y - m_MoveSpeed;

			if (m_UsingBounds)
			{
				delta = SDL_clamp(delta, m_BoundsRect.y + GetHeight(), m_BoundsRect.y + m_BoundsRect.h - GetHeight() * 2);
			}

			SetY(delta);

		}

		void UDRLController::MoveDown()
		{
			int delta = (int)GetPosition().y + m_MoveSpeed;

			if (m_UsingBounds)
			{
				delta = SDL_clamp(delta, m_BoundsRect.y + GetHeight(), m_BoundsRect.y + m_BoundsRect.h - GetHeight() * 2);
			}

			SetY(delta);
		}

		void UDRLController::MoveRight()
		{
			int delta = (int)GetPosition().x + m_MoveSpeed;

			if (m_UsingBounds)
			{
				delta = SDL_clamp(delta, m_BoundsRect.x + GetWidth(), m_BoundsRect.x + m_BoundsRect.w - GetWidth() * 2);
			}

			SetX(delta);
		}

		void UDRLController::MoveLeft()
		{
			int delta = (int)GetPosition().x - m_MoveSpeed;

			if (m_UsingBounds)
			{
				delta = SDL_clamp(delta, m_BoundsRect.x + GetWidth(), m_BoundsRect.x + m_BoundsRect.w - GetWidth() * 2);
			}

			SetX(delta);
		}
	}
}