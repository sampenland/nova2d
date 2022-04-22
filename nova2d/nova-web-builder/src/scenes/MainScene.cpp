#include "MainScene.h"
#include "gui/imgui/imgui.h"
#include "core/Game.h"

namespace webbuilder
{
	using namespace novazero::core;

	MainScene::MainScene(const std::string& sceneName)
		: Scene(sceneName)
	{

	}

	void MainScene::Start()
	{
		m_GUICleanID = n2dAddGUIUpdater(MainScene::DrawGUI, this);
	}

	void MainScene::DrawGUI()
	{
		ImGui::Begin("nova2d Web Builder");

		ImGui::Text("Project 'src' directory");
		ImGui::InputText(" ", m_SrcDirectory, 300);

		// Emscripten add-on libraries
		ImGui::Text("Compile Flags");
		ImGui::Checkbox("Optomize", &m_Optomize);
		ImGui::Checkbox("Web GL 2", &m_UseWebGL2);
		ImGui::Checkbox("SDL 2", &m_UseSDL2);
		ImGui::Checkbox("SDL Mixer 2", &m_UseSDL2Mixer);
		ImGui::Checkbox("SDL TTF", &m_UseSDLTTF);
		ImGui::Checkbox("SDL Image", &m_UseSDLImage);
		ImGui::Checkbox("PNG formats", &m_UseSDLPNG);
		ImGui::Checkbox("OGG & MP3 formats", &m_UseOGGandMP3);
		ImGui::Checkbox("Package 'res' folder", &m_PackageResFolder);

		ImGui::End();
	}

	void MainScene::Update()
	{

		
	}

	void MainScene::End()
	{

	}

	void MainScene::DestroySelf()
	{
		n2dRemoveGUIUpdater(m_GUICleanID);
	}
}