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

		n2dAssetsLoadAndAddTexture("particle", "res/default-particle.png");

		const float pad = 2;
		m_AssetSize = Vec2(16, 16);
		m_AssetPosition = Vec2(Game::s_Width - m_AssetSize.x * pad * 2, m_AssetSize.y * pad);

		m_AssetBackground = new DrawRect("transparent", "white", false, 
			Rect((float)m_AssetPosition.x, (float)m_AssetPosition.y, (float)16, (float)16), 2, 99);

		m_Asset = new Sprite("particle",
			Vec2(m_AssetPosition.x + m_AssetSize.x / 2, m_AssetPosition.y + m_AssetSize.y / 2),
			Vec2Int(16, 16), 100);

		m_ParticleSystem = n2dAddParticleSystem("particle", Vec2Int(16, 16),
			"ps", 100, 5, 10);
		m_ParticleSystem->SetLifetime(2.f, 4.f);

		m_ParticleSystem->ConfigureEmitter("res/default-particle.png", true, 100.f, 10.f, 5.f,
			Vec2(Game::GetCenterScreen().x * 0.45f, Game::GetCenterScreen().y));

		m_MinAngle = m_ParticleSystem->GetEmitAngleMinRef();
		m_MaxAngle = m_ParticleSystem->GetEmitAngleMaxRef();

		m_SystemOn = m_ParticleSystem->GetEmitterEnabled();

		m_MinAngleInput = new ScrollInput("##minAngle", 0.f, 360.f, m_MinAngle);
		m_MaxAngleInput = new ScrollInput("##maxAngle", 0.f, 360.f, m_MaxAngle);

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

		ImGui::Text("Particle Texture");
		ImGui::InputText("##AssetPath", m_ParticleSystem->GetAssetPath(), 200);

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