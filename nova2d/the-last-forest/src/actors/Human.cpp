#include "Human.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::physics;

		Human::Human(Vec2 position, Vec2Int size, unsigned char layer)
		{
			AddSprite("human", position, size, layer);

			ConfigureCollider(GetSprite(), 0, "human");

			// Configure move speed
			Configure(850, false);

			// Program walk downwards
			AddPatrolPointWithFunction(Vec2(position.x, position.y + Game::s_Height - 88), GetLinearPatrolMove());

			// Start walk
			EnableAI(true);
		}

		void Human::OnCollision(Collision* collision)
		{
			LOGS("collision");
		}
	}
}