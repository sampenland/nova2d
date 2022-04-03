#pragma once
#include "controllers/UDRLController.h"
#include "graphics/Image.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::controllers;
		using namespace scenes;

		enum class HighlighterPosition
		{
			Up, Right, Down, Left
		};

		class Player 
			: public UDRLController
		{

		private:

			HighlighterPosition m_Hightlighter = HighlighterPosition::Up;
			Image* m_Highlight = nullptr;
			Image* m_HoldingItem = nullptr;

		public:

			Player(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

			void Update() override;
			void Highlight();

			void HoldItem();
			void PlaceItem();

		public:

			static unsigned int s_HighlightedGridPos;
			static GridTypes s_HoldingItem;
			
			static void PickupItem(GridTypes type);

		private:

			static bool s_ReadyToPlace;
		};
	}
}