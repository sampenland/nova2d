#include "GroundPlayer.h"

namespace spaceshooter
{
	
	GroundPlayer::GroundPlayer(Vec2 position, Vec2Int size, char layer)
		: UDRLController("ground-player", position, size, layer), Collider(0)
	{
		SetPosition(position);
		GetSprite()->SetScale(2.f);

		ConfigureMove(10.f, TweenTypes::EaseInCubic, 100.f, 100.f);

		Deleteable::m_CleanUpdaters.push_back(n2dAddUpdater(GroundPlayer::Update, this));

	}

	void GroundPlayer::Update()
	{
		
	}

	void GroundPlayer::OnCollision(Collision* collision)
	{

	}

	void GroundPlayer::DestroySelf()
	{
		Deleteable::CleanUpdaters();
	}

}