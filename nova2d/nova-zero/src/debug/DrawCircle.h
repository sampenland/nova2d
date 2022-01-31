#pragma once
#include "../graphics/Drawable.h"
#include "../core/Deleteable.h"
#include "../graphics/gfx/SDL2_gfxPrimitives.h"

namespace novazero
{
	namespace debug
	{
		using namespace graphics;
		using namespace core;

		class DrawCircle :
			public Drawable,
			public Deleteable
		{

		private:

			int m_Radius = 1;
			int m_CleanID = 0;
			bool m_Filled = false;
			std::string m_OutlineColor = "";
			std::string m_FillColor = "";

		public:

			DrawCircle(std::string filleColor, std::string outlineColor, bool filled, Vec2 position, int radius, char layer);

			void Draw() override;
			void DestroySelf();

		};
	}
}