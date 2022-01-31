#pragma once
#include "../graphics/Drawable.h"
#include "../maths/Vec2Int.h"
#include "../core/Deleteable.h"
#include "../graphics/Text.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;
		using namespace core;

		class DebugOverlay : public Drawable, public Deleteable
		{

		private:

			bool m_Visible = false;
			Text* m_FPS = nullptr;
			Text* m_Drawables = nullptr;
			Text* m_Updaters = nullptr;
			Text* m_Deletables = nullptr;
			Text* m_References = nullptr;
			Text* m_Gravers = nullptr;
			Text* m_Tweens = nullptr;
			Text* m_TimeEffects = nullptr;
			Text* m_TimeEffecteds = nullptr;

		public:

			DebugOverlay(Vec2Int position);

			void Update();
			void Draw() override;

			void Show() { m_Visible = true; }
			void Hide() { m_Visible = false; }

			void DestroySelf();

		};
	}
}