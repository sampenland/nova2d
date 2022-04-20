#pragma once
#include "controllers/BasicController.h"
#include "graphics/Image.h"

namespace testproject
{
	using namespace novazero::physics;
	using namespace novazero::components;
	using namespace novazero::graphics;

	using namespace novazero::controllers;

	class Player
		: public BasicController
	{

	private:

		int m_Fuel = 5;
		Image* m_FuelDisplay[5];

	public:

		Player(Vec2 position, Vec2 size, unsigned char layer);

		void Update();

		void DestroySelf();

	};
}