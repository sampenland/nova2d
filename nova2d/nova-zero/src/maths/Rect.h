#pragma once

namespace novazero
{
	namespace maths
	{
		struct Rect
		{
			float x, y, w, h;

			Rect(float x, float y, float w, float h)
			{
				this->x = x;
				this->y = y;
				this->w = w;
				this->h = h;
			}

			Rect(int x, int y, int w, int h)
			{
				this->x = (float)x;
				this->y = (float)y;
				this->w = (float)w;
				this->h = (float)h;
			}

		};
	}
}