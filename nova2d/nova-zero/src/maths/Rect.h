#pragma once
#include <iostream>

namespace novazero
{
	namespace maths
	{
		struct Rect
		{
			float x, y, w, h;

			Rect(float x, float y, float w, float h);
			Rect(int x, int y, int w, int h);
			bool operator==(const Rect& other);
			friend std::ostream& operator<<(std::ostream& stream, const Rect& toPrint);

		};
	}
}