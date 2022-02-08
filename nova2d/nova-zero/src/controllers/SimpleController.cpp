#include "SimpleController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;
		using namespace core;

		SimpleController::SimpleController(const std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: EventListener()
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
			Game::s_SceneManager->s_TimeEffectorManager->AddEffected(this);
			ConfigureTimeEffected(m_Sprite);
		}

		SimpleController::~SimpleController()
		{
			if (m_Sprite)
				m_Sprite->DestroySelf();
		}

		void SimpleController::SetMoveSpeed(float mSpeed)
		{
			m_MoveSpeed = mSpeed;

			m_CurrentAccelerationX = mSpeed;
			m_CurrentAccelerationY = mSpeed;
		}

		void SimpleController::SetAcceleration(AccelerationTypes type, float accelerationTimeMS, float deaccelerationTimeMS)
		{
			m_AccelerationType = type;
			m_TotalAccelerationSpeedMS = accelerationTimeMS;
			m_TotalDeaccelerationSpeedMS = deaccelerationTimeMS;

			if (type == AccelerationTypes::Linear)
			{
				m_AccelerationTweenX = n2dTweenAddFloat(&m_CurrentAccelerationX, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, true);
				n2dTweenEnable(m_AccelerationTweenX, false, true);
				m_CurrentAccelerationX = 0;

				m_AccelerationTweenY = n2dTweenAddFloat(&m_CurrentAccelerationY, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, true);
				n2dTweenEnable(m_AccelerationTweenY, false, true);
				m_CurrentAccelerationY = 0;
			}

			m_UsingAcceleration = true;
		}

		void SimpleController::MovementIsZeroX()
		{
			if (m_CurrentAccelerationX < 1 && m_Velocity != Vec2(0.0f, 0.0f))
			{
				m_Velocity.x = 0.f;
			}

			if (m_StoppingX)
			{
				if (m_AccelerationTweenX && m_CurrentAccelerationX > 0)
				{
					// deaccelerate
					m_StoppingX = true;

					switch (m_AccelerationType)
					{
					case AccelerationTypes::Linear:
					default:
						n2dTweenReconfigure(m_AccelerationTweenX, m_CurrentAccelerationX, 0, m_TotalDeaccelerationSpeedMS, false, false);
						n2dTweenEnable(m_AccelerationTweenX, true, false);
						break;
					}
				}
			}
		}

		void SimpleController::MovementIsZeroY()
		{
			if (m_CurrentAccelerationY < 1 && m_Velocity.y != 0.0f)
			{
				m_Velocity.y = 0.f;
			}

			if (m_StoppingY)
			{
				if (m_AccelerationTweenY && m_CurrentAccelerationY > 0)
				{
					// deaccelerate
					m_StoppingY = true;

					switch (m_AccelerationType)
					{
					case AccelerationTypes::Linear:
					default:
						n2dTweenReconfigure(m_AccelerationTweenY, m_CurrentAccelerationY, 0, m_TotalDeaccelerationSpeedMS, false, false);
						n2dTweenEnable(m_AccelerationTweenY, true, false);
						break;
					}
				}
			}
		}

		void SimpleController::SetPositionInt(int x, int y)
		{
			m_Sprite->SetX((float)x);
			m_Sprite->SetY((float)y);
		}

		void SimpleController::SetPosition(float x, float y)
		{
			m_Sprite->SetX(x);
			m_Sprite->SetY(y);
		}

		void SimpleController::SetX(float x)
		{
			m_Sprite->SetX(x);
		}

		void SimpleController::SetY(float y)
		{
			m_Sprite->SetY(y);
		}

		void SimpleController::DestroySelf()
		{
			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffected(this);
		}
	}
}