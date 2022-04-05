#include "Placement.h"
#include "../scenes/AllScenes.h"
#include "../GameDesigner.h"

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
			m_GridPos = gridPos;

			float ox = 0.f;
			float oy = 0.f;

			std::string assetName = "";
			switch (type)
			{
			case GridTypes::Free:
				assetName = "error";
				break;
			case GridTypes::PTree:
				assetName = "trees";
				ox = -35.5f;
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
			position.x += 35.5f + ox;
			position.y += 4.f + oy;

			AddSprite(assetName, Vec2(position.x, position.y + 4), size, layer);
			ConfigureCollider(GetSprite(), 0, "tree");

			m_SunDisplay = new SimpleStatBar(false, position.x - 33.5f, position.y,
				140, 10, "purple", "purple", "yellow", 0);

			m_WaterDisplay = new SimpleStatBar(false, position.x - 33.5f, position.y + 78,
				140, 10, "purple", "purple", "dark-blue", 0);

			if (type == GridTypes::PTree)
			{
				m_DelayDisplay = new SimpleStatBar(false, position.x - 33.5f - ox, position.y + 78,
					140, 10, "purple", "purple", "green", 12);
			}
			else
			{
				m_DelayDisplay = new SimpleStatBar(false, position.x - 33.5f - ox, position.y + 10,
					140, 68, "transparent", "transparent", "highlight", 12);
			}

			auto cleanID = n2dAddUpdater(Placement::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void Placement::RestoreHealth()
		{
			m_HumanDelay = m_HumanDelayMax;
		}

		void Placement::AddResource(bool trueSunFalseWater, float val)
		{
			if (trueSunFalseWater)
			{
				m_Sunlight += val;
				if (m_Sunlight > 100.f) m_Sunlight = 100.f;
			}
			else
			{
				m_Water += val;
				if (m_Water > 100.f) m_Water = 100.f;
			}
		}

		void Placement::SetVisibleStats(bool sun, bool water, bool delay)
		{
			if(m_SunDisplay)
				m_SunDisplay->SetVisible(sun);
			
			if(m_WaterDisplay)
				m_WaterDisplay->SetVisible(water);
			
			if(m_DelayDisplay)
				m_DelayDisplay->SetVisible(delay);
		}

		void Placement::SetEnableStats(bool sun, bool water)
		{
			m_UseSun = sun;
			m_UseWater = water;
		}

		GridTypes Placement::GetType() const
		{
			return m_Type;
		}

		void Placement::Update()
		{
			if (m_Destroyed) return;

			if (m_Type == GridTypes::DeadPTree)
			{
				return;
			}

			if (m_Type == GridTypes::PTree && m_HumanDelay <= 0)
			{
				m_Type = GridTypes::DeadPTree;

				if(GetSprite())
					GetSprite()->SwapTexture("deadtrees");
				
				m_DelayDisplay->SetVisible(false);

				return;
			}

			if (m_Sunlight < 0 || m_Water < 0 || m_HumanDelay <= 0)
			{
				m_Destroyed = true;
				Timer* t = new Timer(500.f, false, n2dMakeFunc(Placement::DestroySelf, this));
				return;
			}

			if(m_UseSun)
				m_Sunlight -= n2dDeltaTime / g_SunDrainTime;
			
			if(m_UseWater)
				m_Water -= n2dDeltaTime / g_WaterDrainTime;

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
			m_Type = GridTypes::Free;

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