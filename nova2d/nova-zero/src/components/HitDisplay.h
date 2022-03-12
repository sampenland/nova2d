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
			public Deleteable
		{

		private:

			unsigned int m_ID = 0;

			Text* m_Display = nullptr;
			unsigned int m_YTweenID;

		protected:

		public:

			HitDisplay(const std::string& startText, const std::string& fontName, const std::string& colorName,
				Rect drawRect, Vec2 endPos, float startToEndTimeMS, unsigned char layer);

			void DestroySelf();

		};
	}
}