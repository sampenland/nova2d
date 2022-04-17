#pragma once
#include "physics/PhySprite.h"
#include "components/SimpleStatBar.h"
#include "graphics/Image.h"

namespace testproject
{
	using namespace novazero::physics;
	using namespace novazero::components;
	using namespace novazero::graphics;

	class Player
		: public PhySprite
	{

	private:

		SimpleStatBar* m_HealthBar = nullptr;
		float m_Health = 100.f;

		int m_Fuel = 5;
		Image* m_FuelDisplay[5];

	public:

		Player(Vec2 position, Vec2 size, unsigned char layer);

		void Update();
		void Controls();

		void DestroySelf();

	};
}