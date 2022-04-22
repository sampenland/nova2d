#pragma once
#include "core/Scene.h"

namespace webbuilder
{
	using namespace novazero::core;

	class MainScene :
		public Scene
	{

	private:

		unsigned int m_GUICleanID = 0;

		bool m_CreateMakefile = true;
		bool m_Optomize = true;
		bool m_UseWebGL2 = true;
		bool m_UseSDL2 = true;
		bool m_UseSDLTTF = true;
		bool m_UseSDLImage = true;
		bool m_UseSDLPNG = true;
		bool m_UseOGGandMP3 = true;
		bool m_UseSDL2Mixer = true;
		bool m_PackageResFolder = true;

		char m_SrcDirectory[300];

	public:

		MainScene(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void DrawGUI();

		void End() override;

		void DestroySelf();
	};
}