#pragma once
#include <iostream>
#include "../maths/Vec4.h"
#include <SDL_stdinc.h>

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		struct Color
		{
			Uint8 r, g, b, a;

			Color()
			{
				r = 255;
				g = 255;
				b = 255;
				a = 255;
			}

			int* GetRRef() { return (int*)&r; }
			int* GetGef() { return (int*)&g; }
			int* GetBRef() { return (int*)&b; }
			int* GetARef() { return (int*)&a; }

			Color(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}	

			Vec4 GetNormalized() const
			{
				Vec4 norm((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
				return norm;
			}

			bool operator==(const Color& other)
			{
				return r == other.r && g == other.g && b == other.b && a == other.a;
			}

			bool operator!=(const Color& other)
			{
				return !(*this == other);
			}

			friend std::ostream& operator<<(std::ostream& stream, const Color& color)
			{
				stream << "Color: [" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << "]";
				return stream;
			}

		};
	}
}