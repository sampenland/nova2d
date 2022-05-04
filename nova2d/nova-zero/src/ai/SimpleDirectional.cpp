#include "SimpleDirectional.h"
#include "../core/Game.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;

		SimpleDirectional::SimpleDirectional(Vec2 targetPosition, float speed, float destroyTimeSeconds, const std::string& assetName, Vec2 position, 
			Vec2Int size, unsigned char layer, const std::string& colliderName, 
			const std::string& collisionGroup)
			: m_Speed(speed/10.f), 
			Sprite(assetName, position, size, layer)
		{
			m_Sensor = new PhySensor(colliderName, false, position, (float)size.x * 0.6f, collisionGroup);
			
			m_Direction = Vec2::LookAtVec(position, targetPosition, true);

			Timer* t = new Timer(destroyTimeSeconds * 1000.f, false, n2dMakeFunc(SimpleDirectional::DestroySelf, this));

			auto cleanID = n2dAddUpdater(SimpleDirectional::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void SimpleDirectional::Update()
		{
			Vec2 currentPos = GetPosition();
			Vec2 newPos = Vec2::VectorStepping(currentPos, m_Direction, m_Speed);
			
			SetPosition(newPos);
			m_Sensor->SetBodyPosition(Vec2(newPos.x, newPos.y));
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