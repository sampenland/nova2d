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

			float m_Radius = 1;
			int m_CleanID = 0;
			bool m_Filled = false;
			bool m_Visible = true;
			std::string m_OutlineColor = "";
			std::string m_FillColor = "";

		public:

			DrawCircle(const std::string& filleColor, const std::string& outlineColor, 
				bool filled, Vec2 position, float radius, char layer);

			float GetDrawCircleRadius() { return m_Radius; }
			float* GetDrawCircleRadiusRef() { return &m_Radius; }
			bool IsDrawCircleFilled() { return m_Filled; }
			void SetDrawCircleRadius(float r) { m_Radius = r; }

			void SetVisible(bool v) { m_Visible = v; }

			void Draw(float oX = 0.f, float oY = 0.f) override;
			void DestroySelf();

		};
	}
}