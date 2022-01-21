#pragma once

namespace novazero
{
	namespace graphics
	{
		class Drawable
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