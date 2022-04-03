#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace novazero::core;

		class MainMenu : public Scene
		{

		private:

			Text* m_Title = nullptr;

		public:

			MainMenu(const std::string& sceneName);

			void Start() override;

			void Update() override;

			void End() override;

			void DestroySelf();

		};
	}
}