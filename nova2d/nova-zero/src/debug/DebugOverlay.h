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
			Text* m_Instances = nullptr;
			Text* m_Updaters = nullptr;

		public:

			DebugOverlay(Vec2Int position);
			~DebugOverlay();

			void Update();
			void Draw() override;

			void Show() { m_Visible = true; }
			void Hide() { m_Visible = false; }

			void DestroySelf();

		};
	}
}