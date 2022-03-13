#include "core/NovaCore.h"
#include "Pawn.h"
#include "../../Player.h"
#include "PawnController.h"

namespace spaceshooter
{
	Pawn::Pawn(const std::string& assetName, Vec2 position, Vec2Int size, char layer, float* moveUpdateDelay,
		float shootMin, float shootMax, int startHealth)
		: SimpleWeakAI()
	{
		m_DeleteName = assetName + tostring(SimpleWeakAI::Collider::m_ID);

		SetPosition(position);
		AddSprite(assetName, position, size, layer);

		GetSprite()->SetScale(2.f);

		ConfigureCollider(GetSprite(), 0, "pawn");
		ConfigureUsingBounds(false, false);

		const int healthBarWidth = 32;

		m_Health = startHealth;
		m_HealthRatio = healthBarWidth / startHealth;
		m_HealthBar = new SimpleStatBar(false, (int)GetX(), (int)GetY() - 2,
			healthBarWidth, 4, "light-blue", "bright-blue", "white", layer);
		m_HealthBar->ConfigureThickness(1);
		m_HealthBar->ConfigureForeground("white", "yellow", "red");
		m_HealthBar->Scale(2.f);

		auto cleanID = n2dAddUpdater(Pawn::PawnUpdate, this);
		m_CleanUpdaters.push_back(cleanID);

		AddPatrolPointWithFunction(Vec2(GetX(), GetY() + 200), GetLinearPatrolMove());
		
		EnableAI(true);

		n2dAddDeleteable(this);
	}

	void Pawn::PawnUpdate()
	{
		if (!m_Alive) return;

		m_HealthBar->Update(m_Health * m_HealthRatio, (int)GetX(), (int)GetY() - 8);

	}

	void Pawn::DisplayHit(int damage)
	{
		Vec2 pos = GetSprite()->GetPosition();
		int width = GetSprite()->GetWidth();

		HitDisplay* hitDisplay = new HitDisplay("+ " + tostring(damage), "font4", "green", 
			Rect(pos.x + width / 2, pos.y - 16.f, 24.f, 16.f),
			Vec2(pos.x, pos.y - 128), 4000, 0);
		LOGS(pos.y);
	}

	void Pawn::Hurt(int damage)
	{
		SmallExplosion();

		m_Health -= damage;
		DisplayHit(damage);

		if (m_Health < 1)
		{
			n2dScoreAdd(15);
			Player::NewKill();
			DestroySelf();
		}
	}

	void Pawn::SmallExplosion()
	{
		Sprite* explosion = new Sprite("explode", GetPosition(), Vec2Int(16, 16), 0);
		explosion->SetScale(2.f);
		auto animEnd = new auto ([](Sprite* sprite) {
			sprite->DestroySelf();
		});
		explosion->AddAnimation("explode", 0, 5, 100.f, false, *animEnd);
	}

	void Pawn::DestroySelf()
	{
		if (m_Destroyed) return;
		m_Destroyed = true;

		m_Alive = false;

		PawnController::s_KilledPawns++;
		PawnController::s_KilledPawnsThisWave++;

		m_UsingCollider = false;

		if (m_HealthBar)
			m_HealthBar->DestroySelf();

		if (GetSprite())
			GetSprite()->DestroySelf();

		m_Dead = 1;
	}
}