#pragma once
#include "core/Scene.h"
#include "../actors/Player.h"
#include "../actors/Alien.h"
#include "physics/PhySensor.h"

namespace testproject
{
	using namespace novazero::core;
	using namespace novazero::physics;

	class Play : public Scene
	{

	private:

		Player* player1 = nullptr;
		Player* player2 = nullptr;

		Image* planetDisplay = nullptr;
		PhySensor* planet = nullptr;
		Alien* alien = nullptr;

	public:

		Play(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}