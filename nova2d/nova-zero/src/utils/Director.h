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

		public:

			Director(Vec2Int position);

			void Update();
			void Draw(float oX = 0.f, float oY = 0.f) override;

			void Show() { m_Visible = true; }
			void Hide() { m_Visible = false; }
			void Toggle() { m_Visible = !m_Visible; }

			void DestroySelf();

		};
	}
}