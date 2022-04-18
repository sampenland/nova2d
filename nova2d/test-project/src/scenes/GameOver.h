#pragma once
#include "core/Scene.h"

namespace testproject
{
	using namespace novazero::core;
	using namespace novazero::physics;

	class GameOver : public Scene
	{

	private:

		

	public:

		GameOver(const std::string& sceneName);

		void Start() override;

		void Update() override;

		void End() override;

		void DestroySelf();

	};
}