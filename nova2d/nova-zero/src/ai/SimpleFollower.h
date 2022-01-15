#pragma once

#include "../maths/Vec2.h"
#include "../maths/Rect.h"
#include "../core/Game.h"
#include "../core/Removeable.h"

namespace novazero
{
	namespace ai
	{
		using namespace graphics;
		using namespace maths;
		using namespace core;

		class SimpleFollower
			: public core::EventListener,
			public core::Removeable
		{

		private:

			Positional* m_Target;
			Vec2Int m_TargetOffset;

			float m_UpdateDirectionDelay = 0;
			float m_DelayTime = 0;
			
		protected:
			Sprite* m_Sprite = nullptr;
			int m_MoveSpeed = 0;
			Rect m_AliveBounds;

		public:

			SimpleFollower(Positional* target, const float moveUpdateDelay);
			~SimpleFollower();

			void AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			void Configure(int moveSpeed, Rect aliveBounds);
			void Offset(Vec2Int offset) { m_TargetOffset = offset; }
			
			void Update();
			bool OutOfBounds();

			bool CheckAlive() override;
			void DestroySelf() override;

		};
	}
}