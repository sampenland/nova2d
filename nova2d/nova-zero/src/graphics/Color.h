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
			float h, s, l;

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

				// Create HSL color as well
				float hsl[3];
				Uint8 rr = r;
				Uint8 gg = g;
				Uint8 bb = b;
				RGB2HSL(rr, gg, bb, hsl);
			}	

			/*
				outRGB is a pointer to value (RGB will be returned in this)
			*/
			void HSL2RGB(float h, float s, float l, Uint8 outRGB[3])
			{
				Uint8 r, g, b;

				if (s == 0) 
				{
					r = g = b = l; // achromatic
				}
				else 
				{
					auto hue2rgb = [=](float p, float q, float t) {
						if (t < 0) t += 1;
						if (t > 1) t -= 1;
						if (t < 1 / 6) return p + (q - p) * 6 * t;
						if (t < 1 / 2) return q;
						if (t < 2 / 3) return p + (q - p) * (2 / 3 - t) * 6;
						return p;
					};

					float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
					float p = 2 * l - q;
					r = hue2rgb(p, q, h + 1 / 3);
					g = hue2rgb(p, q, h);
					b = hue2rgb(p, q, h - 1 / 3);
				}

				r = (Uint8)std::round(r);
				g = (Uint8)std::round(g);
				b = (Uint8)std::round(b);

			}

			/*
				outHSL is a pointer to value (HSL will be returned in this)
			*/
			void RGB2HSL(Uint8& r, Uint8& g, Uint8& b, float outHSL[3])
			{
				r /= 255;
				g /= 255;
				b /= 255;

				Uint8 max = 1;// std::max(r, g, b);
				Uint8 min = 1;// std::min(r, g, b);
				
				float h = outHSL[0];
				float s = outHSL[1];
				float l = outHSL[2];

				h = (max + min) / 2;
				s = (max + min) / 2;
				l = (max + min) / 2;

				if (max == min) 
				{
					h = s = 0; // achromatic
				}
				else 
				{
					Uint8 d = max - min;

					s = l > 0.5 ? d / (2 - max - min) : d / (max + min);

					if (max == r)
					{
						h = (g - b) / d + (g < b ? 6 : 0);
					}
					else if (max == g)
					{
						h = (b - r) / d + 2;
					}
					else if (max == b)
					{
						h = (r - g) / d + 4;
					}

					h /= 6;
				}
			}

			/*
				CurrentColor is a reference to the color being transitioned
			*/
			static Color Interpolate(Color& currentColor, Color a, Color b, float speed)
			{
				currentColor.r = (b.r - a.r) * speed + a.r;
				currentColor.g = (b.g - a.g) * speed + a.g;
				currentColor.b = (b.b - a.b) * speed + a.b;
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