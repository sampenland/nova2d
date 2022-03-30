#include "Rect.h"

namespace novazero
{
	namespace maths
	{
		Rect::Rect(float x, float y, float w, float h)
		{
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		Rect::Rect(int x, int y, int w, int h)
		{
			this->x = (float)x;
			this->y = (float)y;
			this->w = (float)w;
			this->h = (float)h;
		}

		bool Rect::operator==(const Rect& other)
		{
			return x == other.x && y == other.y && w == other.w && h == other.h;
		}

		std::ostream& operator<<(std::ostream& stream, const Rect& toPrint)
		{
			stream << "Rect [" << toPrint.x << ", " << toPrint.y << ", " << toPrint.w << ", " << toPrint.h << "]";
			return stream;
		}
	}
}