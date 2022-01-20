#pragma once
#include "core/Scene.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class GamePlay :
		public Scene
	{

	public:

		GamePlay();
		~GamePlay();

		void Start() override;
		void End() override;

		void Update() override;
	};
}