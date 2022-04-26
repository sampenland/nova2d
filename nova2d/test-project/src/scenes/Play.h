#pragma once
#include "core/Scene.h"
#include "../actors/Player.h"
#include "../actors/Alien.h"
#include "physics/PhySensor.h"
#include "core/Timer.h"
#include "../actors/Human.h"

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

		Timer* m_HumanCreator = nullptr;
		std::vector<Human*> m_Humans;

	public:

		Play(const std::string& sceneName);

		void CreateHuman();

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}