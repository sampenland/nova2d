#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class Play : public Scene
	{

	private:

		Text* m_ScoreText = nullptr;
		Text* m_P1StreakText = nullptr;

	public:

		Play(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

	};
}