#include "MainScene.h"
#include "gui/imgui/imgui.h"
#include "core/Game.h"
#include "thirdparty/dirent/dirent.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <thirdparty/unistd.h>

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

		ImGui::Text("Copy/Paste project 'src' directory");
		ImGui::InputText(" ", m_SrcDirectory, 300);

		ImGui::Checkbox("Create makefile", &m_CreateMakefile);

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

		// --------------------------------------------------------

		ImGui::Begin("'src' directory");

		if (m_ShowSRCDirectroy)
		{
			for (auto dir : m_SrcDirectories)
			{
				ImGui::Checkbox(dir.first.c_str(), &dir.second);
			}
		}

		ImGui::End();
	}

	void MainScene::UpdateSRCDirectory(const std::string& srcDir)
	{
		const char* dir = srcDir.c_str();

		if (chdir(dir) == -1) {
			LOG(LVL_NFE, "SRC directory not found.", __FILE__, __LINE__);
			return;
		}

		DIR* dirp = opendir(dir);

		m_SrcDirectories.clear();

		for (struct dirent* dent; (dent = readdir(dirp)) != NULL; )
		{
			const char* nm = dent->d_name;
			m_SrcDirectories[nm] = true;

			if (strcmp(nm, ".") == 0 || strcmp(nm, "..") == 0)
				continue;

			struct stat file_stats;
			if (stat(nm, &file_stats) == -1)
			{
				std::string err = nm;
				LOG(LVL_NFE, "Err:" + err, __FILE__, __LINE__);
			}
		}

		closedir(dirp);
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