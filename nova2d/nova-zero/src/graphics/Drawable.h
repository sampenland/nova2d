#pragma once
#include "../core/Positional.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		class Drawable : public Positional
		{

		protected:
			
			Drawable();
			~Drawable();

		public:

			char m_Layer = 0;
			unsigned int m_ID = 0;

			virtual void Draw() = 0;
		};
	}
}