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
			LinkPositionalDrawable(m_Sprite);
			SetPosition(position);

			Game::s_SceneManager->s_TimeEffectorManager->AddEffected(this);
			ConfigureTimeEffected(m_Sprite);
		}

		void SimpleController::SetMoveSpeed(float mSpeed)
		{
			m_MoveSpeed = mSpeed;

			m_CurrentAccelerationX = mSpeed;
			m_CurrentAccelerationY = mSpeed;
		}

		void SimpleController::SetAcceleration(TweenTypes type, float accelerationTimeMS, float deaccelerationTimeMS)
		{
			m_AccelerationType = type;
			m_TotalAccelerationSpeedMS = accelerationTimeMS;
			m_TotalDeaccelerationSpeedMS = deaccelerationTimeMS;

			m_AccelerationTweenX = n2dTweenAdd(true, &m_CurrentAccelerationX, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, false, TweenTypes::EaseInCubic);
			n2dTweenEnable(m_AccelerationTweenX, false, true);
			m_CurrentAccelerationX = 0;

			m_AccelerationTweenY = n2dTweenAdd(true, &m_CurrentAccelerationY, 0, m_MoveSpeed, m_TotalAccelerationSpeedMS, false, false, TweenTypes::EaseInCubic);
			n2dTweenEnable(m_AccelerationTweenY, false, true);
			m_CurrentAccelerationY = 0;

			m_UsingAcceleration = true;
		}

		void SimpleController::DestroySelf()
		{
			if (m_Sprite)
				m_Sprite->DestroySelf();

			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffected(this);
		}
	}
}