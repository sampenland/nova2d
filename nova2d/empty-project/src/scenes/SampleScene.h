#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"

namespace emptyproject
{
	using namespace novazero::core;

	class SampleScene : public Scene
	{

	private:

		Text* m_NovaTitle = nullptr;

	public:

		SampleScene(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}