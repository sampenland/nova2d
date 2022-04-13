#include "Director.h"
#include "../core/Game.h"
#include "../gui/imgui/imgui.h"

namespace novazero
{
	namespace utils
	{
		using namespace core;
		using namespace input;

		Director::Director()
		{ }

		void Director::Draw()
		{
			ImGui::Begin("Director");

			ImGui::SliderFloat("Timescale", &Game::s_TimeScale, 0.1f, 6.f);
			
			if(m_LightingSlider)
				m_LightingSlider->Draw();
			
			ImGui::End();
		}

		void Director::InitLighting()
		{
			m_LightingSlider = new ScrollInput("Lighting", (Uint8)0, (Uint8)255,
				Game::s_SceneManager->GetCurrentScene()->s_Environment->m_WorldLightingIntensity);
		}

		void Director::DestroySelf()
		{

		}
	}
}