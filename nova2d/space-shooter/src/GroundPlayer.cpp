#include "GroundPlayer.h"

namespace spaceshooter
{
	
	GroundPlayer::GroundPlayer(Vec2 position, Vec2Int size, char layer)
		: UDRLController("ground-player", position, size, layer), Collider(0)
	{
		
	}

	void GroundPlayer::OnCollision(Collision* collision)
	{

	}

}