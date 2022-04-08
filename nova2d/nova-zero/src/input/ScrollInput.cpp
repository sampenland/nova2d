#pragma once
#include "ScrollInput.h"
#include "../gui/imgui/imgui.h"
#include "../core/Game.h"

namespace novazero
{
	namespace input
	{
		ScrollInput::ScrollInput(const std::string& title, float min, float max, float* value)
		{
			m_Title = title;
			m_MinF = min;
			m_MaxF = max;

			m_ValueF = value;

			m_IsFloat = true;

		}
		
		ScrollInput::ScrollInput(const std::string& title, Uint8 min, Uint8 max, Uint8* value)
		{
			m_Title = title;
			m_MinI = min;
			m_MaxI = max;

			m_ValueI = new Uint8;
			m_ValueI = value;

			m_IsFloat = false;
		}

		Uint8 ScrollInput::GetValueI() const
		{
			return *m_ValueI;
		}

		float ScrollInput::GetValueF() const
		{
			return *m_ValueF;
		}

		void ScrollInput::Draw()
		{
			if (m_IsFloat)
			{
				ImGui::SliderFloat(m_Title.c_str(), m_ValueF, m_MinF, m_MaxF);
			} 
			else
			{
				ImGui::SliderInt(m_Title.c_str(), (int*)m_ValueI, m_MinI, m_MaxI);
			}
		}

		void ScrollInput::DestroySelf()
		{
			if (m_IsFloat)
			{
				if (m_ValueF)
					delete m_ValueF;
			}
			else
			{
				if (m_ValueI)
					delete m_ValueI;
			}
		}
	}
}