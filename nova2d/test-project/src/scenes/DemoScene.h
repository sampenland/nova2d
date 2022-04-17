#pragma once
#include "core/Scene.h"
#include "../actors/Player.h"
#include "../actors/Alien.h"
#include "DemoSceneContactListener.h"
#include "physics/PhySensor.h"

namespace testproject
{
	using namespace novazero::core;
	using namespace novazero::physics;

	class DemoScene : public Scene
	{

	private:

		DemoSceneContactListener* m_ContactListener = nullptr;

		Player* player = nullptr;
		Image* planetDisplay = nullptr;
		PhySensor* planet = nullptr;
		Alien* alien = nullptr;

	public:

		DemoScene(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}