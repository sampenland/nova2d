#include "Rocket.h"
#include "core/Game.h"
#include "core/Timer.h"

namespace testproject
{
	using namespace novazero::core;

	Rocket::Rocket(const std::string& player, Vec2 position, Positional* target, float moveDelay)
		: PhySimpleFollower(target, moveDelay)
	{

		AddSprite("rocket", position, Vec2Int(16, 16), 3);
		GetSprite()->AddAnimation("spin", 0, 4, 10, true, nullptr);

		AddPhySensor(player + "_rocket", false, position, 6, "rockets");

		Timer* destructTimer = new Timer(4000.f, false, n2dMakeFunc(Rocket::DestroySelf, this));
		ConfigureRotation(true, 0);
	}

	void Rocket::DestroySelf()
	{
		CleanUpdaters();
		PhySimpleFollower::DestroySelf();
		SetDeleted(true);
	}
}