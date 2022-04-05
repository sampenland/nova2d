#pragma once
#include "graphics/Image.h"
#include "../Enums.h"
#include "ai/SimpleWeakAI.h"
#include "components/SimpleStatBar.h"

namespace thelastforest
{
	namespace placements
	{
		using namespace novazero::graphics;
		using namespace novazero::ai;
		using namespace novazero::components;

		class Placement :
			public SimpleWeakAI
		{

		private:

			GridTypes m_Type = GridTypes::Free;
			unsigned int m_GridPos = 0;

			unsigned int m_HumanDelay = 0;
			unsigned int m_HumanDelayMax = 0;

			SimpleStatBar* m_SunDisplay = nullptr;
			SimpleStatBar* m_WaterDisplay = nullptr;
			SimpleStatBar* m_DelayDisplay = nullptr;

			float m_Sunlight = 100.f;
			float m_Water = 100.f;

			bool m_UseWater = true;
			bool m_UseSun = true;

			bool m_Destroyed = false;

		public:

			Placement() {};
			Placement(GridTypes type, unsigned int humanDelay,
				unsigned int gridPos, Vec2Int size, unsigned char layer);

			GridTypes GetType() const;

			void SetVisibleStats(bool sun, bool water, bool delay);
			void SetEnableStats(bool sun, bool water);

			void AddResource(bool trueSunFalseWater, float val);
			void RestoreHealth();

			void Update();

			bool UseDelay(int delay);

			void DestroySelf();

		};
	}
}