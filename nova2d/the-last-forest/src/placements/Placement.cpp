#include "Placement.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace placements
	{
		using namespace novazero::graphics;
		using namespace scenes;

		Placement::Placement(GridTypes type, unsigned int humanDelay,
			unsigned int gridPos, Vec2Int size, unsigned char layer)
		{
			
			m_HumanDelay = humanDelay;
			m_HumanDelayMax = humanDelay;

			m_Type = type;

			std::string assetName = "";
			switch (type)
			{
			case GridTypes::Free:
				assetName = "error";
				break;
			case GridTypes::PTree:
				break;
			case GridTypes::DeadPTree:
				break;
			case GridTypes::Tree:
				assetName = "tree";
				break;
			case GridTypes::Grass:
				break;
			case GridTypes::Water:
				break;
			case GridTypes::Sun:
				break;
			}

			Vec2 position = AllScenes::GetPositionFromTile(gridPos, 9);
			position.x += 35.5f;
			position.y += 4.f;

			AddSprite(assetName, position, size, layer);
			ConfigureCollider(GetSprite(), 0, "tree");

			AllScenes::SetGridPosition(gridPos, type);

			m_SunDisplay = new SimpleStatBar(false, position.x - 33.5f, position.y,
				140, 10, "purple", "purple", "yellow", 2);

			m_WaterDisplay = new SimpleStatBar(false, position.x - 33.5f, position.y + 78,
				140, 10, "purple", "purple", "dark-blue", 2);

			m_DelayDisplay = new SimpleStatBar(false, position.x - 33.5f, position.y + 10,
				140, 68, "transparent", "transparent", "highlight", 2);

			auto cleanID = n2dAddUpdater(Placement::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		GridTypes Placement::GetType() const
		{
			return m_Type;
		}

		void Placement::Update()
		{
			if (m_Destroyed) return;

			if (m_Sunlight < 0 || m_Water < 0 || m_HumanDelay <= 0)
			{
				m_Destroyed = true;
				Timer* t = new Timer(500.f, false, n2dMakeFunc(Placement::DestroySelf, this));
				return;
			}

			m_Sunlight -= n2dDeltaTime / 30;
			m_Water -= n2dDeltaTime / 10;

			SimpleWeakAI::Update();

			m_SunDisplay->Update((m_Sunlight / 100.f) * 142, m_SunDisplay->GetX(),
				m_SunDisplay->GetY());

			m_WaterDisplay->Update((m_Water / 100.f) * 142, m_WaterDisplay->GetX(),
				m_WaterDisplay->GetY());

			int delaySize = (int)((float)m_HumanDelay / (float)m_HumanDelayMax * 142.f);
			m_DelayDisplay->Update(delaySize, m_DelayDisplay->GetX(),
				m_DelayDisplay->GetY());

		}

		bool Placement::UseDelay(int delay)
		{
			m_HumanDelay -= delay;
			return m_HumanDelay == 0;
		}

		void Placement::DestroySelf()
		{
			if (m_SunDisplay)
				m_SunDisplay->DestroySelf();

			if (m_WaterDisplay)
				m_WaterDisplay->DestroySelf();

			if (m_DelayDisplay)
				m_DelayDisplay->DestroySelf();

			CleanUpdaters();
			SimpleWeakAI::DestroySelf();
		}
	}
}