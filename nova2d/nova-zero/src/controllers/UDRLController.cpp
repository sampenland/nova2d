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

		UDRLController::UDRLController(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer,
			char controllerID)
			: SimpleController(assetName, position, size, layer)
		{
			m_JoyStickNumber = controllerID;

			auto cleanID = n2dAddUpdater(UDRLController::UpdateController, this);
			SimpleController::m_CleanUpdaters.push_back(cleanID);
		}

		void UDRLController::ConfigureMove(float moveSpeed)
		{
			SetMoveSpeed(moveSpeed);
		}

		void UDRLController::UpdateController()
		{
			Update();

			bool right = n2dIsKeyDown(SDLK_RIGHT) || n2dJoySimpleRight(m_JoyStickNumber);
			bool left = n2dIsKeyDown(SDLK_LEFT) || n2dJoySimpleLeft(m_JoyStickNumber);

			bool down = n2dIsKeyDown(SDLK_DOWN) || n2dJoySimpleDown(m_JoyStickNumber);
			bool up = n2dIsKeyDown(SDLK_UP) || n2dJoySimpleUp(m_JoyStickNumber);

			float speed = m_MoveSpeed * n2dTimeScale * GetTimeInfluence();

			Vec2 pos = GetSprite()->GetPosition();

			float newX = pos.x;
			float newY = pos.y;

			if (right)
			{
				newX += speed;
			}
			else if (left)
			{
				newX -= speed;
			}

			if (up)
			{
				newY -= speed;
			}
			else if (down)
			{
				newY += speed;
			}

			if (pos != Vec2(newX, newY))
			{
				if (newX > pos.x) SetFacing(Directions::Right);
				if (newX < pos.x) SetFacing(Directions::Left);
				if (newY < pos.y) SetFacing(Directions::Up);
				if (newY > pos.y) SetFacing(Directions::Down);

				if (IsWithinMoveBounds((int)newX, (int)pos.y, m_MoveOffsets.x, m_MoveOffsets.y))
				{
					SetX(newX / CAMERA_ZOOM);
				}

				if (IsWithinMoveBounds((int)pos.x, (int)newY, m_MoveOffsets.x, m_MoveOffsets.y))
				{
					SetY(newY / CAMERA_ZOOM);
				}
			}				
		}

		void UDRLController::SetX(float x)
		{
			Positional::SetX(x);
			GetSprite()->SetX(x);
		}

		void UDRLController::SetY(float y)
		{
			Positional::SetY(y);
			GetSprite()->SetY(y);
		}

		void UDRLController::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;

			SimpleController::CleanUpdaters();
			SimpleController::DestroySelf();

			SimpleController::SetDeleted(true);
		}

	}
}