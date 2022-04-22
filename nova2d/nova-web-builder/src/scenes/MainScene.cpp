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
		ImGui::InputText(" ", m_SrcDirectory, 500);

		if (ImGui::Button("Update directories"))
		{
			MainScene::UpdateSRCDirectory(m_SrcDirectory);
			m_ShowSRCDirectroy = true;
		}

		if (m_ShowSRCDirectroy)
		{
			for (auto dir : m_SrcDirectories)
			{
				ImGui::Checkbox(dir.first.c_str(), dir.second);
			}
		}

		ImGui::End();

		// ---------------------------------------------
		if (m_CreateMakefile)
		{

			ImGui::Begin("makefile settings");

			ImGui::Text("box2d.a directory (no trailing / or filename)");
			ImGui::InputText(" ", m_Box2dDirectory, 500);
			ImGui::Text("novalib.a directory (no trailing / or filename)");
			ImGui::InputText(" ", m_NovaDirectory, 500);

			if (ImGui::Button("Update Makefile"))
			{
				UpdateMakefile();
			}

			ImGui::InputTextMultiline(" ", m_MakefileBuffer, 8192, ImVec2(575, 380), 
				ImGuiInputTextFlags_ReadOnly);

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

		// CPP FLags
		makefileText += "\nCPPFLAGS := -DNOVA_EMSCRIPTEN -s LLD_REPORT_UNDEFINED ";
		
		std::string b2dDir = m_Box2dDirectory;
		std::string novaDir = m_NovaDirectory;
		
		makefileText += " " + b2dDir + "/box2d.a ";
		makefileText += " " + novaDir + "/novalib.a ";

		if (m_Optomize)
		{
			makefileText += " -O2 ";
		}

		if (m_UseWebGL2)
		{
			makefileText += " -s USE_WEBGL2=1 ";
		}

		if (m_UseSDL2)
		{
			makefileText += " -s USE_SDL=2 ";
		}

		if (m_UseSDLTTF)
		{
			makefileText += " -s USE_SDL_TTF=2 ";
		}

		if (m_UseSDLImage)
		{
			makefileText += " -s USE_SDL_IMAGE=2 ";
		}

		if (m_UseSDLPNG)
		{
			makefileText += " -s SDL2_IMAGE_FORMATS='[\"png\"]' ";
		}

		if (m_UseSDL2Mixer)
		{
			makefileText += " - s SDL2_MIXER_FORMATS = [ogg, mp3] - s USE_SDL_MIXER = 2 - s USE_OGG = 1 - s USE_VORBIS = 1 - s USE_MPG123 = 1 - s USE_MODPLUG = 1";
		}
		
		if (m_PackageResFolder)
		{
			std::string resFolder = m_ResDirectory;
			makefileText += " --preload-file " + resFolder;
		}

		makefileText += "\n\n";

		makefileText += "I1 := -I" + b2dDir + "\n";

		makefileText += "I2 := -I" + novaDir + "\n\n";

		makefileText += "src := ";
		for (auto dir : m_SrcDirectories)
		{
			if ((*dir.second))
			{
				makefileText += "$(wildcard " + dir.first + "/*.cpp) ";
			}
		}

		makefileText += "\n\n";

		makefileText += "all:\n";
		makefileText += "\t$(CPP) $(CPPFLAGS) $(I1) $(I2) $(SRCS) - o index.js";

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
						std::string p = path;
						while (p.find("\\") != std::string::npos)
						{
							p = p.replace(p.find("\\"), 1, "/");
						}
						bool* val = new bool;
						*val = true;
						m_SrcDirectories[p] = val;
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