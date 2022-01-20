#pragma once
#include "core/Scene.h"

namespace spaceshooter
{
	using namespace novazero::core;

	class Lvl1 :
		public Scene
	{

	public:

		Lvl1();
		~Lvl1();

		void Start() override;
		void End() override;

		void Update() override;
	};
}