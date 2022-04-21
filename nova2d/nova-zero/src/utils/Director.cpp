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
		{
		}

		void Director::Draw()
		{
			ImGui::Begin("Director");

			ImGui::Text("Running: %.3f ms/frame (%.1f FPS)",
				1000.0 / float(ImGui::GetIO().Framerate), float(ImGui::GetIO().Framerate));
			
			if (Game::s_SceneManager->GetCurrentScene())
			{
				if (Game::s_SceneManager->GetCurrentScene()->m_PhysicsEnabled)
				{
					ImGui::Checkbox("Debug Physics: ", &Game::s_SceneManager->GetCurrentScene()->m_DebugDraw);
				}
			}

			ImGui::Text("Drawables: %d", n2dDebugDrawableCount());
			ImGui::Text("Deleteables: %d", n2dDebugDeleteableCount());
			ImGui::Text("Updaters: %d", n2dDebugUpdaterCount());
			ImGui::Text("References: %d", n2dDebugReferencedCount());
			ImGui::Text("Tweens: %d", n2dDebugTweenCount());
			
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