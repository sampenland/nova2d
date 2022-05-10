#include "EditorScene.h"
#include "core/Game.h"
#include "gui/imgui/imgui.h"

namespace particleeditor
{
	EditorScene::EditorScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void EditorScene::Start()
	{
		EnablePhysics(true);

		n2dAssetsLoadAndAddTexture("particle", "res/particles/smoke_01.png");

		const float pad = 2;
		const float scale = 0.25f;
		m_AssetSize = Vec2Int(512, 512);
		m_AssetPosition = Vec2(Game::s_Width - m_AssetSize.x * scale * 2, 8);

		m_AssetBackground = new DrawRect("transparent", "white", false, 
			Rect((float)m_AssetPosition.x, (float)m_AssetPosition.y, 
				(float)m_AssetSize.x * scale, (float)m_AssetSize.y * scale), 2, 99);

		m_Asset = new Sprite("particle", Vec2(m_AssetPosition.x + m_AssetSize.x * scale / 2,
			m_AssetPosition.y + m_AssetSize.y * scale / 2),
			m_AssetSize, 100, scale);

		m_ParticleSystem = n2dAddParticleSystem("particle", m_AssetSize,
			"ps", 100, 5, 10);
		m_ParticleSystem->SetEditorFeature(true);
		m_ParticleSystem->SetScale(scale);
		m_ParticleSystem->SetLifetime(2.2f, 2.2f);

		m_ParticleSystem->ConfigureEmitter("res/particles/smoke_01.png", true, 100.f, 2.f, 5.f,
			Vec2(Game::GetCenterScreen().x * 0.48f, Game::GetCenterScreen().y));

		m_MinAngle = m_ParticleSystem->GetEmitAngleMinRef();
		m_MaxAngle = m_ParticleSystem->GetEmitAngleMaxRef();

		m_EmitterSpeed = m_ParticleSystem->GetEmitterSpeedRef();

		m_MinLifetime = m_ParticleSystem->GetMinLifeTimeRef();
		m_MaxLifetime = m_ParticleSystem->GetMaxLifeTimeRef();

		m_SystemOn = m_ParticleSystem->GetEmitterEnabled();

		m_MaxParticles = m_ParticleSystem->GetMaxParticleRef();
		m_ParticleRadius = m_ParticleSystem->GetParticleRadiusRef();

		m_EmitterVelocity = m_ParticleSystem->GetEmitterVelocityRef();

		m_StartAlpha = m_ParticleSystem->GetStartAlphaRef();
		m_StartAlphaRnd = m_ParticleSystem->GetStartAlphaRndRef();

		m_EndAlpha = m_ParticleSystem->GetEndAlphaRef();
		m_EndAlphaRnd = m_ParticleSystem->GetEndAlphaRndRef();

		m_AlphaChangeSpeed = m_ParticleSystem->GetAlphaChangeSpeedRef();
		m_UsingAlphaTransition = m_ParticleSystem->GetUsingAlphaTransitionRef();

		m_UsingColorTransition = m_ParticleSystem->GetUsingColorTransitionRef();
		m_ColorTransition = m_ParticleSystem->GetColorTransitionRef();
		m_ColorTransSpeed = &m_ColorTransition->Speed;
		*m_ColorTransSpeed = 0.0025f;
		m_ColorTransSpeed2 = &m_ColorTransition->Speed2;
		*m_ColorTransSpeed2 = 0.0025f;

		m_StartColor = m_ParticleSystem->GetStartColorRef();
		m_MidColor = m_ParticleSystem->GetMidColorRef();
		m_EndColor = m_ParticleSystem->GetEndColorRef();
		m_ColorTransSpeedInput = new ScrollInput("##colorTransSpeed", 0.001f, 0.2f, m_ColorTransSpeed);
		m_ColorTransSpeed2Input = new ScrollInput("##colorTransSpeed2", 0.001f, 0.2f, m_ColorTransSpeed2);

		m_MinAngleInput = new ScrollInput("##minAngle", 0.f, 360.f, m_MinAngle);
		m_MaxAngleInput = new ScrollInput("##maxAngle", 0.f, 360.f, m_MaxAngle);

		m_EmitterSpeedInput = new ScrollInput("##emitterSpeed", 0.f, 1000.f, m_EmitterSpeed);

		m_MinLifetimeInput = new ScrollInput("##minLifetime", 0.f, 12.f, m_MinLifetime);
		m_MaxLifetimeInput = new ScrollInput("##maxLifetime", 0.f, 12.f, m_MaxLifetime);
		
		m_MaxParticleInput = new ScrollInput("##maxParticles", 1, 255, m_MaxParticles);

		m_ParticleRadiusInput = new ScrollInput("##particleRadius", 1, 255, m_ParticleRadius);
		m_EmitterVelocityInput = new ScrollInput("##emitterVelocity", 0.15f, 150.f, m_EmitterVelocity);

		m_StartAlphaInput = new ScrollInput("##startAlpha", 0, 255, m_StartAlpha);
		m_StartAlphaRndInput = new ScrollInput("##startAlphaRnd", 0, 127, m_StartAlphaRnd);

		m_EndAlphaInput = new ScrollInput("##endAlpha", 0, 255, m_EndAlpha);
		m_EndAlphaRndInput = new ScrollInput("##endAlphaRnd", 0, 127, m_EndAlphaRnd);

		m_AlphaChangeSpeedInput = new ScrollInput("##alphaChangeSpeed", 0.5f, 10.f, m_AlphaChangeSpeed);

		auto cleanID = n2dAddGUIUpdater(EditorScene::GUI, this);

	}

	void EditorScene::GUI()
	{
		ImGui::Begin("Settings");

		ImGui::Separator();

		ImGui::Checkbox("System On", m_SystemOn);
		ImGui::SameLine();
		ImGui::Checkbox("Debug Physics", &Game::s_SceneManager->GetCurrentScene()->m_DebugDraw);

		ImGui::Separator();

		ImGui::Text("Max Particles");
		ImGui::SameLine();
		ImGui::Text("Particles: %d", n2dDebugParticleCount());
		m_MaxParticleInput->Draw();

		ImGui::Separator();

		ImGui::Text("Particle Texture");
		//ImGui::InputText("##AssetPath", m_ParticleSystem->GetAssetPath(), 200);

		if (ImGui::CollapsingHeader("Physics"))
		{
			ImGui::Text("Particle Radius");
			ImGui::SameLine();
			m_ParticleRadiusInput->Draw();
		}		

		if (ImGui::CollapsingHeader("Emitter"))
		{
			ImGui::Text("Emit Interval");
			ImGui::SameLine();
			m_EmitterSpeedInput->Draw();

			ImGui::Text("Emitter Velocity");
			ImGui::SameLine();
			m_EmitterVelocityInput->Draw();

			ImGui::Indent();
			if (ImGui::CollapsingHeader("Emission Angle"))
			{
				ImGui::Text("Min. Angle");
				ImGui::SameLine();
				m_MinAngleInput->Draw();
				ImGui::Text("Max. Angle");
				ImGui::SameLine();
				m_MaxAngleInput->Draw();
			}
			ImGui::Unindent();

		}

		if (ImGui::CollapsingHeader("Lifetime"))
		{
			ImGui::Text("Particle Lifetime");
			ImGui::Text("Min");
			ImGui::SameLine();
			m_MinLifetimeInput->Draw();
			ImGui::Text("Max");
			ImGui::SameLine();
			m_MaxLifetimeInput->Draw();
		}

		if (ImGui::CollapsingHeader("Color"))
		{
			ImGui::Indent();

			ImGui::Text("Using Color Transition");
			ImGui::SameLine();
			ImGui::Checkbox("##usingColorTrans", m_UsingColorTransition);

			if (*m_UsingColorTransition)
			{
				ImGui::Separator();

				ImGui::Text("Start Transition Speed");
				ImGui::SameLine();
				m_ColorTransSpeedInput->Draw();

				ImGui::Separator();

				ImGui::Text("Middle Transition Speed");
				ImGui::SameLine();
				m_ColorTransSpeed2Input->Draw();

				ImGui::Separator();

				if (ImGui::CollapsingHeader("Start"))
				{
					ImGui::ColorPicker3("##startColor", m_StartColor);
				}

				if (ImGui::CollapsingHeader("Mid"))
				{
					ImGui::ColorPicker3("##midColor", m_MidColor);
				}

				if (ImGui::CollapsingHeader("End"))
				{
					ImGui::ColorPicker3("##endColor", m_EndColor);
				}

				m_ColorTransition->Enabled = *m_UsingColorTransition;

				m_ColorTransition->Start.r = (Uint8)(255 * m_StartColor[0]);
				m_ColorTransition->Start.g = (Uint8)(255 * m_StartColor[1]);
				m_ColorTransition->Start.b = (Uint8)(255 * m_StartColor[2]);
				m_ColorTransition->Start.HSLUpdate();

				m_ColorTransition->Mid.r = (Uint8)(255 * m_MidColor[0]);
				m_ColorTransition->Mid.g = (Uint8)(255 * m_MidColor[1]);
				m_ColorTransition->Mid.b = (Uint8)(255 * m_MidColor[2]);
				m_ColorTransition->Mid.HSLUpdate();

				m_ColorTransition->End.r = (Uint8)(255 * m_EndColor[0]);
				m_ColorTransition->End.g = (Uint8)(255 * m_EndColor[1]);
				m_ColorTransition->End.b = (Uint8)(255 * m_EndColor[2]);
				m_ColorTransition->End.HSLUpdate();
			}

			ImGui::Unindent();
		}

		if (ImGui::CollapsingHeader("Alpha"))
		{
			ImGui::Checkbox("Use Alpha Transition", m_UsingAlphaTransition);

			ImGui::Indent();

			ImGui::Text("Alpha Transition Speed");
			ImGui::SameLine();
			m_AlphaChangeSpeedInput->Draw();
			ImGui::Text("Alpha Start");
			ImGui::SameLine();
			m_StartAlphaInput->Draw();
			ImGui::Text("Start Rand.");
			ImGui::SameLine();
			m_StartAlphaRndInput->Draw();

			ImGui::Separator();

			ImGui::Text("Alpha End");
			ImGui::SameLine();
			m_EndAlphaInput->Draw();
			ImGui::Text("End Rand.");
			ImGui::SameLine();
			m_EndAlphaRndInput->Draw();

			ImGui::Unindent();
		}

		ImGui::End();

	}

	void EditorScene::Update()
	{
		/*
		
		Used to test certain things per particle
		
		if (n2dMouseJustDown())
		{
			m_ParticleSystem->BurstSingleParticle(n2dGetMousePosition(SDL_BUTTON_LEFT),
				255, 1, 40.f, 10.f, 5.f, 80, 100);
		}*/
	}

	void EditorScene::End()
	{

	}

}