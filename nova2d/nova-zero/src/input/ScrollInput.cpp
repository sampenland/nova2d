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
		
		ScrollInput::ScrollInput(const std::string& title, int32 min, int32 max, int32* value)
		{
			m_Title = title;
			m_MinI32 = min;
			m_MaxI32 = max;

			m_ValueI32 = new int32;
			m_ValueI32 = value;

			m_IsFloat = false;
		}

		int ScrollInput::GetValueI32() const
		{
			return *m_ValueI32;
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
				ImGui::SliderInt(m_Title.c_str(), m_ValueI32, m_MinI32, m_MaxI32);
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
				if (m_ValueI32)
					delete m_ValueI32;
			}
		}
	}
}