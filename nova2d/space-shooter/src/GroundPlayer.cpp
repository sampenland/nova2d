#include "GroundPlayer.h"

namespace spaceshooter
{
	
	GroundPlayer::GroundPlayer(Vec2 position, Vec2Int size, char layer)
		: UDRLController("ground-player", position, size, layer)
	{
		SetPosition(position);
		GetSprite()->SetScale(2.f);

		ConfigureMove(2.f);
		ConfigureMoveOffsets(Origins::Centered, GetSprite());
		ConfigureMoveBounds(Game::GetGameBounds());
		ConfigureUsingBounds(true, false);

		Deleteable::m_CleanUpdaters.push_back(n2dAddUpdater(GroundPlayer::Update, this));

	}

	void GroundPlayer::Update()
	{
		
	}

	void GroundPlayer::DestroySelf()
	{
		Deleteable::CleanUpdaters();
	}

}