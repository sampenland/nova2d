#include "Player.h"

namespace testproject
{
	Player::Player(Vec2 position, Vec2Int size, unsigned char layer)
		: PhySprite("player", position, size, layer)
	{
		ConfigurePhysicsRect("player", false);
	}
}