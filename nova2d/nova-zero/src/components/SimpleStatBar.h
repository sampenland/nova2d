#pragma once
#include "../core/Positional.h"
#include "../maths/Rect.h"
#include "../graphics/Drawable.h"

namespace novazero
{
	using namespace core;
	using namespace maths;
	using namespace graphics;

	namespace components
	{
		class SimpleStatBar
			: public Positional, public Drawable
		{

		private:

			Rect m_Bar;

		public:

			SimpleStatBar();
			~SimpleStatBar();

			void Update();
			void Draw() override;

		};
	}
}