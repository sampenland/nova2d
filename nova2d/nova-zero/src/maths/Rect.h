#pragma once

namespace novazero
{
	namespace maths
	{
		struct Rect
		{
			int x, y, w, h;

			Rect(int x, int y, int w, int h)
			{
				this->x = x;
				this->y = y;
				this->w = w;
				this->h = h;
			}

		};
	}
}