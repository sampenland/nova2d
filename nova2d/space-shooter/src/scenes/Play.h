#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"
#include "../enemies/pawns/PawnController.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class Play : public Scene, public NovaInstance
	{

	private:

		Text* m_ScoreText = nullptr;
		Text* m_P1StreakText = nullptr;
		Text* m_Waves = nullptr;

		PawnController* m_PawnController = nullptr;

	public:

		Play(const std::string& sceneName);

		void Start() override;

		bool NoPawns();
		
		void ShowWaveAnimation(unsigned char wave);

		void Wave1();
		void Wave2();
		void Wave3();
		void Wave4();
		void Wave5();

		void Update() override;

		void End() override;

		// Nova Instance
		void CreateInstance(Vec2 pos) override {};

	};
}