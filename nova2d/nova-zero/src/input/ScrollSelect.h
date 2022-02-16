#pragma once
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"
#include "../debug/DrawRect.h"
#include "../graphics/Text.h"
#include "../core/Defines.h"

namespace novazero
{
	namespace input
	{
		using namespace core;
		using namespace graphics;
		using namespace debug;

		class ScrollSelect :
			public Drawable,
			public Deleteable
		{

		private:

			bool m_Visible = true;
			bool m_Destroyed = false;

			int m_Width = 100;
			int m_Height = 20;

			Text* m_Label = nullptr;
			DrawRect* m_Background = nullptr;
			DrawRect* m_ScrollRect = nullptr;

			Text* m_TextMin = nullptr;
			Text* m_TextVal = nullptr;
			Text* m_TextMax = nullptr;

			int m_Min = 0;
			int m_Max = 0;
			int m_Ref;

		public:

			ScrollSelect(std::string labelText, int labelWidth, std::string textColor,
				float width, float height, float min, float max, float* refVal,
				Rect background, std::string backgroundColor, std::string scrollColor,
				BYTE layer);

			void Draw(float oX = 0.f, float oY = 0.f) override;
			void SetVisible(bool isVisible);

			void Update();

			void DestroySelf();

		};
	}
}