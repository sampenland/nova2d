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
		m_ParticleSystem->SetScale(scale);
		m_ParticleSystem->SetLifetime(2.f, 4.f);

		m_ParticleSystem->ConfigureEmitter("res/particles/smoke_01.png", true, 100.f, 10.f, 5.f,
			Vec2(Game::GetCenterScreen().x * 0.48f, Game::GetCenterScreen().y));

		m_MinAngle = m_ParticleSystem->GetEmitAngleMinRef();
		m_MaxAngle = m_ParticleSystem->GetEmitAngleMaxRef();

		m_EmitterSpeed = m_ParticleSystem->GetEmitterSpeedRef();

		m_MinLifetime = m_ParticleSystem->GetMinLifeTimeRef();
		m_MaxLifetime = m_ParticleSystem->GetMaxLifeTimeRef();

		m_SystemOn = m_ParticleSystem->GetEmitterEnabled();

		m_MaxParticles = m_ParticleSystem->GetMaxParticleRef();

		m_MinAngleInput = new ScrollInput("##minAngle", 0.f, 360.f, m_MinAngle);
		m_MaxAngleInput = new ScrollInput("##maxAngle", 0.f, 360.f, m_MaxAngle);

		m_EmitterSpeedInput = new ScrollInput("##emitterSpeed", 0.f, 5000.f, m_EmitterSpeed);

		m_MinLifetimeInput = new ScrollInput("##minLifetime", 0.f, 12.f, m_MinLifetime);
		m_MaxLifetimeInput = new ScrollInput("##maxLifetime", 0.f, 12.f, m_MaxLifetime);
		
		m_MaxParticleInput = new ScrollInput("##maxParticles", 1, 255, m_MaxParticles);

		auto cleanID = n2dAddGUIUpdater(EditorScene::GUI, this);

	}

	void EditorScene::GUI()
	{
		ImGui::Begin("Settings");

		ImGui::Separator();

		ImGui::Checkbox("System On", m_SystemOn);
		ImGui::SameLine();
		ImGui::Checkbox("Debug Physics", &Game::s_SceneManager->GetCurrentScene()->m_DebugDraw);
		ImGui::SameLine();
		ImGui::Text("Particles: %d", n2dDebugParticleCount());

		ImGui::Separator();

		ImGui::Text("Max Particles");
		ImGui::SameLine();
		m_MaxParticleInput->Draw();

		ImGui::Separator();
		
		ImGui::Text("Emit Interval");
		ImGui::SameLine();
		m_EmitterSpeedInput->Draw();

		ImGui::Separator();

		ImGui::Text("Particle Texture");
		ImGui::InputText("##AssetPath", m_ParticleSystem->GetAssetPath(), 200);

		ImGui::Separator();
		ImGui::Text("Particle Lifetime");
		ImGui::Text("Min");
		ImGui::SameLine();
		m_MinLifetimeInput->Draw();
		ImGui::Text("Max");
		ImGui::SameLine();
		m_MaxLifetimeInput->Draw();

		ImGui::Separator();
		ImGui::Text("Emission Angle");
		ImGui::Text("Min Angle");
		ImGui::SameLine();
		m_MinAngleInput->Draw();
		ImGui::Text("Max Angle");
		ImGui::SameLine();
		m_MaxAngleInput->Draw();

		ImGui::End();
	}

	void EditorScene::Update()
	{
		
	}

	void EditorScene::End()
	{

	}

}