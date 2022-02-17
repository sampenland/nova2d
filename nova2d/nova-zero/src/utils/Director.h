#pragma once
#include "../graphics/Drawable.h"
#include "../maths/Vec2Int.h"
#include "../core/Deleteable.h"
#include "../graphics/Text.h"
#include "../debug/DrawRect.h"
#include "../input/ScrollSelect.h"
#include <vector>

namespace novazero
{
	namespace utils
	{
		using namespace graphics;
		using namespace core;
		using namespace debug;
		using namespace input;

		struct DirectorPage
		{
			std::vector<ScrollSelect*> m_LeftStack;
			std::vector<ScrollSelect*> m_RightStack;
		};

		class Director : 
			public Drawable, 
			public Deleteable
		{

		private:

			Text* m_Title = nullptr;
			DrawRect* m_Background = nullptr;

			ScrollSelect* m_ScrollTime = nullptr;

			int m_Width = 1000;
			int m_Height = 700;

			bool m_SelectionLock = false;
			bool m_LeftSelectedStack = true;
			short m_CurrentSelected = -1;

		protected:

			bool m_Destroyed = false;
			bool m_Visible = false;

		public:

			Director(Vec2Int position = Vec2Int(150, 32));

			void Update();
			void Draw(float oX = 0.f, float oY = 0.f) override;

			void ChangeSelection(ScrollSelect* oldSelected);
			void Toggle();

			void DestroySelf();

		public:

			static const int s_LeftStackX = 160;
			static const int s_RightStackX = 950;
			static const int s_StackStartY = 155;

			static BYTE s_CurrentPage;
			static std::vector<DirectorPage*> s_Pages;
			static void AddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float min, float max, float* refVal);

		};
	}
}