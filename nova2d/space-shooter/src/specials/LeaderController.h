#pragma once
#include "../enemies/Leader.h"
#include "core/Deleteable.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class LeaderController : Deleteable
	{

	private:

		Leader* m_Leader = nullptr;
		int m_Wave = 0;

	public:

		LeaderController();

		void CreateLeader(Vec2 position, int maxHealth, int pawnRows, int pawnCols);

		void Update();
		void DestroySelf();

	public:

		static bool s_LeaderExists;

	};
}