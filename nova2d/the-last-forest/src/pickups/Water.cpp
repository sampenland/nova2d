#include "Water.h"

namespace thelastforest
{
	namespace pickups
	{
		Water::Water(int row)
		{
			float x = 35.5f;
			float y = 4 + (row * 88);
			AddSprite("water", Vec2(-142, y), Vec2Int(71, 70), 0);

			ClearPatrol();

			Configure(1000, false);
			AddPatrolPointWithFunction(Vec2(x, y), GetLinearPatrolMove());
			EnableAI(true);

			ConfigureOnPatrolComplete(n2dMakeFunc(Water::StartWait, this));

		}

		void Water::StartWait()
		{
			Timer* delay = new Timer(5000, false, n2dMakeFunc(Water::DestroySelf, this));
		}

		void Water::DestroySelf()
		{
			SimpleWeakAI::DestroySelf();
			SetDeleted(true);
		}
	}
}