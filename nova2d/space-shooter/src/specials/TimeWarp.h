#pragma once
#include "physics/TimeEffector.h"
#include "core/Timer.h"
#include "core/TimerWatcher.h"
#include "core/Deleteable.h"
#include "graphics/Sprite.h"
#include "physics/Collider.h"
#include "physics/Collision.h"

namespace spaceshooter
{
	using namespace novazero::physics;
	using namespace novazero::core;
	using namespace novazero::graphics;

	class TimeWarp :
		public TimeEffector,
		public TimerWatcher,
		public Collider
	{

	private:

		unsigned int m_CleanID = 0;
		unsigned int m_TweenID = 0;
		int m_EffectRadius = 0;
		Timer* m_PickupLimit = nullptr;
		Timer* m_DestroyTime = nullptr;
		Sprite* m_Sprite = nullptr;

	public:

		TimeWarp(Vec2 position, float timeEffect, int effectRadius, float captureTime);

		void OnCollision(Collision* collision);
		void PickupAndExpand();

		void DestroySelf();

	};
}