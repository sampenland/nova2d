#include "GroundPlayer.h"

namespace spaceshooter
{
	
	GroundPlayer::GroundPlayer(Vec2 position, Vec2Int size, char layer)
		: UDRLController("ground-player", position, size, layer), Collider(0)
	{
		GetSprite()->Scale(2.f);
	}

	void GroundPlayer::OnCollision(Collision* collision)
	{

	}

}