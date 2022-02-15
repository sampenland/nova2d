#pragma once
#include "../graphics/Drawable.h"
#include "../maths/Vec2Int.h"
#include "../core/Deleteable.h"
#include "../graphics/Text.h"

namespace novazero
{
	namespace utils
	{
		using namespace graphics;
		using namespace core;

		class Director : public Drawable, public Deleteable
		{

		private:

			bool m_Visible = false;
			bool m_Destroyed = false;

			Text* m_Title = nullptr;

		public:

			Director(Vec2Int position = Vec2Int(150, 32));

			void Update();
			void Draw(float oX = 0.f, float oY = 0.f) override;

			void Toggle();

			void DestroySelf();

		};
	}
}