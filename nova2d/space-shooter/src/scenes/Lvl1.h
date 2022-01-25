#pragma once
#include "core/Scene.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::graphics;

	class Lvl1 :
		public Scene
	{

	private:

		Text* m_ScoreText = nullptr;

	public:

		Lvl1(std::string sceneName);
		~Lvl1();

		void Start() override;
		void End() override;

		void Update() override;

	public:

		static char s_Players;
	};
}