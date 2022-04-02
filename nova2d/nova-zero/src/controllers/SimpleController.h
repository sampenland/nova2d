#pragma once
#include "../graphics/Sprite.h"
#include "../core/EventListener.h"
#include "../maths/Vec2Int.h"
#include "../utils/TextureLoader.h"
#include "../core/Game.h"
#include "../physics/TimeEffected.h"
#include "../core/Positional.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace graphics;
		using namespace maths;

		class SimpleController :
			public EventListener,
			public TimeEffected,
			public Positional
		{

		private:

			Sprite* m_Sprite = nullptr;

		protected:

		public:

			SimpleController(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

			void SetMoveSpeed(float mSpeed);
			
			inline float GetMoveSpeed() const { return m_MoveSpeed; }

			void DestroySelf();

		private:

		public:

			float m_MoveSpeed = 0.0f;

		};
	}
}