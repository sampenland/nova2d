#include "SimpleDirectional.h"
#include "../core/Game.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;

		SimpleDirectional::SimpleDirectional(Vec2 direction, float speed, float destroyTimeSeconds, const std::string& assetName, Vec2 position, 
			Vec2Int size, unsigned char layer, const std::string& colliderName, 
			const std::string& collisionGroup)
			: m_Direction(direction), m_Speed(speed/10.f), 
			Sprite(assetName, position, size, layer)
		{
			m_Sensor = new PhySensor(colliderName, false, position, (float)size.x * 0.6f, collisionGroup);
			
			Timer* t = new Timer(destroyTimeSeconds * 1000.f, false, n2dMakeFunc(SimpleDirectional::DestroySelf, this));

			auto cleanID = n2dAddUpdater(SimpleDirectional::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void SimpleDirectional::Update()
		{
			Vec2 currentPos = GetPosition();
			Vec2 newPos = Vec2(GetX() + (m_Direction.x * m_Speed * n2dTimeScale),
								GetY() + (m_Direction.y * m_Speed * n2dTimeScale));
			
			SetPosition(newPos);
			m_Sensor->SetBodyPosition(Vec2(newPos.x + GetWidth() / 2, newPos.y + GetWidth() / 2));
		}

		void SimpleDirectional::DestroySelf()
		{
			CleanUpdaters();

			if (m_Sensor)
				m_Sensor->DestroySelf();

			Sprite::DestroySelf();
			SetDeleted(true);
		}
	}
}