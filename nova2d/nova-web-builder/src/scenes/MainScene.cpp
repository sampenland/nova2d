#include "MainScene.h"
#include "gui/imgui/imgui.h"
#include "core/Game.h"
#include "thirdparty/dirent/dirent.h"
#include <sys/types.h>
#include <sys/stat.h>

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

		if (m_PackageResFolder)
		{
			ImGui::Text("'res' directory");
			ImGui::InputText(" ", m_ResDirectory, 300);
		}

		ImGui::End();

		// --------------------------------------------------------

		ImGui::Begin("'src' directory");
		ImGui::Text("Copy/Paste project 'src' directory");
		ImGui::InputText(" ", m_SrcDirectory, 300);

		if (ImGui::Button("Update directories"))
		{
			MainScene::UpdateSRCDirectory(m_SrcDirectory);
			m_ShowSRCDirectroy = true;
		}

		if (m_ShowSRCDirectroy)
		{
			for (auto dir : m_SrcDirectories)
			{
				ImGui::Checkbox(dir.first.c_str(), &dir.second);
			}
		}

		ImGui::End();

		// ---------------------------------------------
		if (m_CreateMakefile)
		{

			ImGui::Begin("makefile settings");

			if (ImGui::Button("Update Makefile"))
			{
				UpdateMakefile();
			}

			ImGui::InputTextMultiline(" ", m_MakefileBuffer, 8192, ImVec2(575, 380));

			if (ImGui::Button("Save Makefile"))
			{
				SaveMakefile();
			}

			ImGui::End();

		}
	}

	void MainScene::SaveMakefile()
	{

	}

	void MainScene::UpdateMakefile()
	{
		std::string makefileText = "CPP := em++ -std=c++14\n";

		// Make makefile string

		const char* makefileTextChars = makefileText.c_str();

		for (int i = 0; i < 8192; i++)
		{
			if (i < (int)makefileText.length())
			{
				m_MakefileBuffer[i] = makefileText[i];
			}
			else
			{
				m_MakefileBuffer[i] = NULL;
			}
		}
	}

	void MainScene::UpdateSRCDirectory(const std::string& srcDir)
	{
		const char* dir = srcDir.c_str();
		m_SrcDirectories.clear();
		GetDirectories(srcDir.c_str());
	}

	int MainScene::GetDirectories(const char* basePath)
	{
		char path[1000];
		struct dirent* dp;
		DIR* dir = opendir(basePath);

		// Unable to open directory stream
		if (!dir)
			return 0;

		int count = 0;
		while ((dp = readdir(dir)) != NULL)
		{
			if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
			{
				// Construct new path from our base path
				strcpy_s(path, basePath);
				strcat_s(path, "/");
				strcat_s(path, dp->d_name);

				if (GetDirectories(path) > 0)
				{
					std::string filename = dp->d_name;
					if (filename.find(".") == std::string::npos)
					{
						m_SrcDirectories[filename] = true;
					}
				}
				count++;
			}
		}

		closedir(dir);

		return count;
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