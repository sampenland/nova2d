#pragma once
#include "../enemies/Leader.h"
#include "core/Deleteable.h"
#include "graphics/Text.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::graphics;

	class LeaderController : Deleteable
	{

	private:

		Leader* m_Leader = nullptr;
		Text* m_Waves = nullptr;

	public:

		LeaderController();

		void CreateLeader(Vec2 position, int maxHealth, int pawnRows, int pawnCols);

		void ShowWaveAnimation();

		void Update();
		void DestroySelf();

	public:

		static bool s_LeaderExists;
		static bool s_LeaderKilled;
		static int s_Wave;

	};
}