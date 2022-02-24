#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"
#include "../specials/LeaderController.h"
#include "../specials/Pawn1Controller.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::graphics;

	class Lvl1 :
		public Scene
	{

	private:

		Text* m_ScoreText = nullptr;
		Text* m_P1StreakText = nullptr;

		LeaderController* m_LeaderController;
		Pawn1Controller* m_Pawn1Controller;

	public:

		Lvl1(const std::string& sceneName);

		void Start() override;
		void End() override;

		void Update() override;

	};
}