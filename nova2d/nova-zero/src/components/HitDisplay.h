#pragma once
#include "../graphics/Text.h"
#include "../core/Deleteable.h"
#include "../graphics/Drawable.h"

namespace novazero
{
	namespace components
	{
		using namespace core;
		using namespace graphics;

		class HitDisplay : 
			public Deleteable,
			public Drawable
		{

		private:

			Text* m_Display = nullptr;
			unsigned int m_XTweenID, m_YTweenID;

		protected:

		public:

			HitDisplay(const std::string& startText, const std::string& fontName, const std::string& colorName,
				Rect drawRect, Vec2 endPos, float startToEndTimeMS, char layer);

			void Update();
			void Draw(float oX = 0.f, float oY = 0.f) override;
			void DestroySelf();

		};
	}
}