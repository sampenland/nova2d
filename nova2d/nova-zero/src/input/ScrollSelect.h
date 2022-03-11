#pragma once
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"
#include "../debug/DrawRect.h"
#include "../graphics/Text.h"
#include "../core/Defines.h"
#include "../input/DirectorStackable.h"

namespace novazero
{
	namespace input
	{
		using namespace core;
		using namespace graphics;
		using namespace debug;

		class ScrollSelect :
			public Drawable,
			public Deleteable,
			public DirectorStackable
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

			const float m_Min = 0;
			float m_Max = 0;
			float m_InOrDecreaseBy = 0.1f;
			float* m_Ref;

		public:

			ScrollSelect(std::string labelText, int labelWidth, std::string textColor,
				float width, float height, float inOrDecreaseBy, float max, float* refVal,
				Rect background, std::string backgroundColor, std::string scrollColor,
				BYTE layer, bool isPersistent = false);

			void Draw(float oX = 0.f, float oY = 0.f, float zoom = 1.f) override;
			void SetVisible(bool isVisible) override;
			void SetEnabled(bool isEnabled) override
			{
				Deleteable::SetEnabled(isEnabled);
			}

			void SetLabelColor(std::string colorName)
			{
				m_Label->SetColor(colorName);
			}

			void SetValueColor(std::string colorName)
			{
				m_TextVal->SetColor(colorName);
			}

			void Update() override;
			void HandleSelected();
			void Select(bool isSelected, const std::string& fillColor, const std::string& outlineColor) override;

			void DestroySelf();

		};
	}
}