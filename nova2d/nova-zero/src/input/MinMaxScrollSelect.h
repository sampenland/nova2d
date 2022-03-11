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

		class MinMaxScrollSelect :
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
			DrawRect* m_MinScrollRect = nullptr;
			DrawRect* m_MaxScrollRect = nullptr;

			Text* m_TextMin = nullptr;
			Text* m_TextMinVal = nullptr;
			Text* m_TextMaxVal = nullptr;
			Text* m_TextMax = nullptr;

			float m_Min = 0;
			float m_Max = 0;

			float m_InOrDecreaseBy = 0.1f;

			float* m_MinRef;
			float* m_MaxRef;

			bool m_MinSelected = true;
			bool m_SelectionLock = false;

		public:

			MinMaxScrollSelect(std::string labelText, int labelWidth, std::string textColor,
				float width, float height, float inOrDecreaseBy, float min, float max, float* minRefVal, float* maxRefVal,
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
				m_TextMinVal->SetColor(colorName);
				m_TextMaxVal->SetColor(colorName);
			}

			void HandleValueChanging();

			void Update() override;
			void HandleSelected();
			void Select(bool isSelected, const std::string& fillColor, const std::string& outlineColor) override;

			void DestroySelf();

		};
	}
}