#pragma once
#include "controllers/BasicController.h"
#include "graphics/Image.h"
#include "core/Timer.h"
#include "particles/ParticleSystem.h"

namespace testproject
{
	using namespace novazero::physics;
	using namespace novazero::components;
	using namespace novazero::graphics;
	using namespace novazero::core;
	using namespace novazero::particles;

	using namespace novazero::controllers;

	class Player
		: public BasicController
	{

	private:

		int m_Fuel = 5;
		float m_FuelTank = 100.f;
		const float FUEL_COST = 0.25f;
		bool m_Fueling = false;

		Image* m_FuelDisplay[5];

		ParticleSystem* m_Jets = nullptr;

	public:

		Player(const std::string& colliderName, Vec2 position, Vec2 size, unsigned char layer);

		void Update();
		void Jets();

		void FuelManage();
		void StartFueling();
		void StopFueling();

		void DestroySelf();

	};
}