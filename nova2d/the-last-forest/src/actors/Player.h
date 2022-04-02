#pragma once
#include "controllers/UDRLController.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::controllers;

		class Player 
			: public UDRLController
		{

		private:

		public:

			Player(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer);

			void Update() override;

		};
	}
}