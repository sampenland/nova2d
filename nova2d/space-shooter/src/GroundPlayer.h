#pragma once
#include "components/SimpleStatBar.h"
#include "controllers/UDRLController.h"
#include "maths/Vec2Int.h"
#include "physics/Collider.h"
#include "core/Referenceable.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::maths;
	using namespace novazero::physics;
	using namespace novazero::controllers;

	class GroundPlayer :
		public UDRLController, public Referenceable,
		public Collider
	{

	private:



	public:

		GroundPlayer(Vec2 position, Vec2Int size, char layer);

		void Update();

		void OnCollision(Collision* collision) override;

		void DestroySelf();

	};
}