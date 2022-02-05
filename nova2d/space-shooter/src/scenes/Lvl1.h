#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"
#include "../specials/LeaderController.h"

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
		Text* m_P2StreakText = nullptr;

		LeaderController* m_LeaderController;

	public:

		Lvl1(std::string sceneName);

		void Start() override;
		void End() override;

		void Update() override;

	public:

		static char s_Players;
	};
}