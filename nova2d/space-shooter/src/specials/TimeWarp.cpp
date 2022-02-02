#include "TimeWarp.h"
#include "core/Game.h"

namespace spaceshooter
{
	TimeWarp::TimeWarp(Vec2 position, float timeEffect, int effectRadius, float captureTime) : 
		TimeEffector(position, timeEffect, effectRadius, Rect((int)position.x, (int)position.y, effectRadius, effectRadius), TimeEffectorType::Circle),
		Collider(0)
	{
		TimeEffector::m_ID = n2dGameGetID();
		m_DeleteName = "timeWarp_" + std::to_string(TimeEffector::m_ID);

		m_CleanID = n2dAddDeleteable(this);

		m_EffectRadius = effectRadius;
		m_PickupLimit = new Timer(captureTime, false, std::bind(&TimeWarp::DestroySelf, this));

		ConfigureTimeEffectorVisible(false, "white", "dark-blue", 0);
		SetEnabled(false);

		m_Sprite = new Sprite("clock", Vec2(position.x - 8, position.y - 8), Vec2Int(16, 16), 0);
		m_Sprite->ConfigureAnimation(0, 4, 250, true);

		int* ptrToRadius = GetEffectorRadiusRef();
		if (ptrToRadius)
		{
			m_TweenID = n2dTweenAddInt(ptrToRadius, effectRadius, 1.0f, 1000.0f, true);
		}

		ConfigureCollider(m_Sprite, 0, "clock");
	}

	void TimeWarp::OnCollision(Collision* collision)
	{
		if (collision->m_ColliderA->m_ColliderName == "clock" && collision->m_ColliderB->m_ColliderName == "player")
		{
			((TimeWarp*)(collision->m_ColliderA))->PickupAndExpand();
		}
		else if (collision->m_ColliderB->m_ColliderName == "clock" && collision->m_ColliderA->m_ColliderName == "player")
		{
			((TimeWarp*)(collision->m_ColliderB))->PickupAndExpand();
		}
	}

	void TimeWarp::PickupAndExpand()
	{
		if (IsEnabled()) return;

		if (m_PickupLimit)
		{
			m_PickupLimit->SetEnabled(false);
			m_PickupLimit->DestroySelf();
		}

		if (m_TweenID != 0)
		{
			n2dTweenRemove(m_TweenID);
		}

		int* ptrToRadius = GetEffectorRadiusRef();
		if (ptrToRadius)
		{
			m_TweenID = n2dTweenAddInt(ptrToRadius, 1.0f, m_EffectRadius, 1000.0f, false);
		}

		m_DestroyTime = new Timer(3000, false, std::bind(&TimeWarp::DestroySelf, this));

		SetEnabled(true);
	}

	void TimeWarp::DestroySelf()
	{
		if (m_PickupLimit)
		{
			m_PickupLimit->SetEnabled(false);
			m_PickupLimit->DestroySelf();
		}

		if (m_DestroyTime)
			m_DestroyTime->DestroySelf();

		if (m_Sprite)
			m_Sprite->DestroySelf();

		TimeEffector::DestroySelf();

		if (m_TweenID != 0)
		{
			n2dTweenRemove(m_TweenID);
		}

		CleanUpdaters();

		SetDeleted(true);
	}
}