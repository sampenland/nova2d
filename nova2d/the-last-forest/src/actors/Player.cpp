#include "Player.h"

namespace thelastforest
{
	namespace actors
	{
		Player::Player(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
			: UDRLController(assetName, position, size, layer)
		{
			ConfigureMove(5.f, TweenTypes::EaseInExpo, 100.f, 100.f);
			ConfigureMoveBounds(Rect(142, 0, Game::s_Width - (2 * 142) - size.x, Game::s_Height - 2 * 88));
		}

		void Player::Update()
		{
			
		}
	}
}