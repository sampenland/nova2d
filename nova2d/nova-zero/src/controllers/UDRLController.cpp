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

		void UDRLController::UpdateController()
		{
			bool pX = n2dIsKeyDown(SDLK_RIGHT) || n2dJoySimpleRight(m_JoyStickNumber);
			bool nX = n2dIsKeyDown(SDLK_LEFT) || n2dJoySimpleLeft(m_JoyStickNumber);

			bool pY = n2dIsKeyDown(SDLK_DOWN) || n2dJoySimpleDown(m_JoyStickNumber);
			bool nY = n2dIsKeyDown(SDLK_UP) || n2dJoySimpleUp(m_JoyStickNumber);

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

			Vec2 pos = GetSprite()->GetPosition();
			float newX = pos.x + (timeScaleX); // fix int casting ROUND downwards to 0 speed issue
			float newY = pos.y + (timeScaleY); // fix int casting ROUND downwards to 0 speed issue

			if (pos != Vec2(newX, newY))
			{
				if (IsWithinMoveBounds((int)newX, (int)pos.y, m_MoveOffsets.x, m_MoveOffsets.y))
				{
					GetSprite()->SetX(newX);
				}

				if (IsWithinMoveBounds((int)pos.x, (int)newY, m_MoveOffsets.x, m_MoveOffsets.y))
				{
					GetSprite()->SetY(newY);
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

			SimpleController::SetDeleted(true);
		}

	}
}