#include "Kamikaze.h"
#include "physics/Collider.h"
#include "components/HitDisplay.h"
#include "../../Player.h"

namespace spaceshooter
{
	using namespace novazero::core;
	using namespace novazero::physics;
	using namespace novazero::components;

	Kamikaze::Kamikaze(Vec2 position, float* speed)
	{
		AddSprite("kamikaze", position, Vec2Int(16, 16), 0);
		GetSprite()->AddAnimation("idle", 0, 16, 10.f, true, nullptr);

		Collider::m_ID = n2dGameGetID();
		m_DeleteName = "kamikaze_" + tostring(Collider::m_ID);

		m_CleanID = n2dAddDeleteable(this);

		Player* player = (Player*)n2dReferenceGet("player");
		AddPatrolPointWithFunction(player->GetPosition(), GetLinearPatrolMove());
				
		Configure(speed, false);
		ConfigureContinueAfterPatrolComplete(true);
		
		auto enableBounds = new auto ([=]() {
			ConfigureAliveBounds(Game::GetGameBounds(32.f));
		});
		Timer* t = new Timer(1000, false, *enableBounds);

		EnableAI(true);

	}

	void Kamikaze::Hurt(int damage)
	{
		SmallExplosion();
		DisplayHit(damage);
	}

	void Kamikaze::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", GetPosition(), Vec2Int(16, 16), 0);
		explosion->Scale(2.f);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
		});
		explosion->AddAnimation("explode", 0, 5, 100.f, false, *animEnd);
	}

	void Kamikaze::DisplayHit(int damage)
	{
		Vec2 pos = GetPosition();
		int width = GetWidth();

		HitDisplay* hitDisplay = new HitDisplay("+ " + std::to_string(damage), "font4", "green", Rect(pos.x - width / 2, GetY() - 16.f, 24.f, 16.f),
			Vec2(pos.x, pos.y - 128), 4000, 0);
	}

	void Kamikaze::DestroySelf()
	{
		CleanUpdaters();

		n2dRemoveDeleteable(m_CleanID);
		SimpleWeakAI::DestroySelf();

		SetDeleted(true);
		
	}

}