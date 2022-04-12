#pragma once
#include "core/Scene.h"
#include "physics/PhySprite.h"
#include "DemoSceneContactListener.h"

namespace testproject
{
	using namespace novazero::core;
	using namespace novazero::physics;

	class DemoScene : public Scene
	{

	private:

		DemoSceneContactListener* m_ContactListener = nullptr;

		PhySprite* player = nullptr;

	public:

		DemoScene(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}