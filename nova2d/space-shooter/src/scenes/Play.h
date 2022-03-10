#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"
#include "../enemies/pawns/PawnController.h"
#include "../enemies/pawns/KamikazeController.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class Play : public Scene, public TimelineInstance
	{

	private:

		Text* m_ScoreText = nullptr;
		Text* m_P1StreakText = nullptr;
		Text* m_Waves = nullptr;

		PawnController* m_PawnController = nullptr;
		KamikazeController* m_KamikazeController = nullptr;

		bool m_SentFuel = false;

	public:

		Play(const std::string& sceneName);

		void Start() override;

		void SendFuel();		
		
		void ShowWaveAnimation(unsigned char wave);

		void Wave1();
		void Wave2();
		void Wave3();
		void Wave4();
		void Wave5();

		void Update() override;

		void End() override;

	};
}