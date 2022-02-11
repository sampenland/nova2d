#include "TimeWarp.h"
#include "core/Game.h"

namespace spaceshooter
{
	TimeWarp::TimeWarp(Vec2 position, float timeEffect, int effectRadius, float captureTime, float destroyMS) : 
		TimeEffector(position, timeEffect, effectRadius, Rect((int)position.x, (int)position.y, effectRadius, effectRadius), TimeEffectorType::Circle),
		Collider(0)
	{
		TimeEffector::m_ID = n2dGameGetID();
		m_DeleteName = "timeWarp_" + std::to_string(TimeEffector::m_ID);
		m_DestroyTime = destroyMS;

		m_CleanID = n2dAddDeleteable(this);

		m_EffectRadius = effectRadius;
		m_PickupLimit = new Timer(captureTime, false, std::bind(&TimeWarp::DestroySelf, this));

		ConfigureTimeEffectorVisible(false, "white", "dark-blue", 0);
		SetEnabled(false);

		m_Sprite = new Sprite("clock", Vec2(position.x - 8, position.y - 8), Vec2Int(16, 16), 0);
		m_Sprite->ConfigureAnimation(0, 4, 4, 250, true);

		int* ptrToRadius = GetEffectorRadiusRef();
		if (ptrToRadius)
		{
			//m_TweenID = n2dTweenAddInt(ptrToRadius, (float)effectRadius, 1.0f, 1000.0f, true, true);
		}

		ConfigureCollider(m_Sprite, 0, "clock");
	}

	void TimeWarp::OnCollision(Collision* collision)
	{
		bool aIsPlayer = collision->m_ColliderA->m_ColliderName == "player1" ||
			collision->m_ColliderA->m_ColliderName == "player2";
		bool bIsPlayer = collision->m_ColliderB->m_ColliderName == "player1" ||
			collision->m_ColliderB->m_ColliderName == "player2";

		if (collision->m_ColliderA->m_ColliderName == "clock" && bIsPlayer)
		{
			((TimeWarp*)(collision->m_ColliderA))->PickupAndExpand();
		}
		else if (collision->m_ColliderB->m_ColliderName == "clock" && aIsPlayer)
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
			//m_TweenID = n2dTweenAddInt(ptrToRadius, 1.0f, (float)m_EffectRadius, 600.0f, false, true);
		}

		m_DestroyTimer = new Timer(m_DestroyTime, false, std::bind(&TimeWarp::DestroySelf, this));

		SetEnabled(true);
	}

	void TimeWarp::DestroySelf()
	{
		if (m_PickupLimit)
		{
			m_PickupLimit->SetEnabled(false);
			m_PickupLimit->DestroySelf();
		}

		if (m_DestroyTimer)
			m_DestroyTimer->DestroySelf();

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