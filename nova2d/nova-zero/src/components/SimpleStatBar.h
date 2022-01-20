#pragma once
#include "../core/Positional.h"
#include "../maths/Rect.h"

namespace novazero
{
	using namespace core;
	using namespace maths;

	namespace components
	{
		class SimpleStatBar
			: public Positional
		{

		private:

			Rect m_Bar;

		public:

			SimpleStatBar();
			~SimpleStatBar();

			void Update();
			void Draw();

		};
	}
}