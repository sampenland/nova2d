#pragma once
#include "core/Scene.h"

namespace testproject
{
	using namespace novazero::core;

	class DemoScene : public Scene
	{

	private:

	public:

		DemoScene(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}