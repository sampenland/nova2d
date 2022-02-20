#pragma once
#include "../core/Positional.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		class DrawableCollection;

		class Drawable : public Positional
		{

		private:

			DrawableCollection* m_DrawableCollection = nullptr;

		protected:
			
			Drawable();

		public:

			unsigned char m_Layer = 0;
			unsigned int m_ID = 0;

			void SetDrawableCollection(DrawableCollection* collection);
			void ClearDrawableCollection(unsigned int id);

			virtual void Draw(float oX = 0.f, float oY = 0.f) = 0;

		};
	}
}