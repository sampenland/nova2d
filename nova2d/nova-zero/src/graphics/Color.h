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

				// Create HSL color as well
				HSLUpdate();

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

			void RGBUpdate()
			{
				Update(this->h, this->s, this->l);
			}

			void HSLUpdate()
			{
				Update(this->r, this->g, this->b);
			}

			void Update(float h, float s, float l)
			{
				// Create HSL color as well
				Uint8 rgb[3];
				HSL2RGB(h, s, l, rgb);
				this->r = rgb[0];
				this->g = rgb[1];
				this->b = rgb[2];
			}

			void Update(Uint8 r, Uint8 g, Uint8 b)
			{
				// Create HSL color as well
				float hsl[3];
				RGB2HSL(r, g, b, hsl);
				this->h = hsl[0];
				this->s = hsl[1];
				this->l = hsl[2];
			}

			/*
				outRGB is a pointer to value (RGB will be returned in this)
			*/
			void HSL2RGB(float h, float s, float l, Uint8 outRGB[3])
			{
				float fr = 0;
				float fg = 0;
				float fb = 0;

				if (s == 0)
				{
					fr = l;
					fg = l;
					fb = l;
				}
				else
				{
					int i;
					float f, p, q, t;

					if (h == 360)
						h = 0;
					else
						h = h / 60;

					i = (int)trunc(h);
					f = h - i;

					p = l * (1.0f - s);
					q = l * (1.0f - (s * f));
					t = l * (1.0f - (s * (1.0f - f)));

					switch (i)
					{
					case 0:
						fr = l;
						fg = t;
						fb = p;
						break;

					case 1:
						fr = q;
						fg = l;
						fb = p;
						break;

					case 2:
						fr = p;
						fg = l;
						fb = t;
						break;

					case 3:
						fr = p;
						fg = q;
						fb = l;
						break;

					case 4:
						fr = t;
						fg = p;
						fb = l;
						break;

					default:
						fr = l;
						fg = p;
						fb = q;
						break;
					}

				}

				outRGB[0] = (Uint8)std::round(fr * 255);
				outRGB[1] = (Uint8)std::round(fg * 255);
				outRGB[2] = (Uint8)std::round(fb * 255);

			}

			/*
				outHSL is a pointer to value (HSL will be returned in this)
			*/
			void RGB2HSL(Uint8 r, Uint8 g, Uint8 b, float outHSL[3])
			{
				r /= 255;
				g /= 255;
				b /= 255;

				Uint8 max = std::max(std::max(r, g), b);
				Uint8 min = std::max(std::min(r, g), b);
				
				float h;
				float s;
				float l;

				h = (max + min) / 2.f;
				s = (max + min) / 2.f;
				l = (max + min) / 2.f;

				if (max == min) 
				{
					h = 0;
					s = 0; // achromatic
				}
				else 
				{
					Uint8 d = max - min;

					s = l > 0.5 ? d / (2.f - max - min) : d / (max + min);

					if (max == r)
					{
						h = (g - b) / d + (g < b ? 6.f : 0.f);
					}
					else if (max == g)
					{
						h = (b - r) / d + 2.f;
					}
					else if (max == b)
					{
						h = (r - g) / d + 4.f;
					}

					h /= 6.f;
				}

				outHSL[0] = h;
				outHSL[1] = s;
				outHSL[2] = l;
			}

			/*
				CurrentColor is a reference to the color being transitioned
			*/
			static void Interpolate(Color& currentColor, Color targetColor, float speed)
			{
				// Hue
				bool low = true;
				if (currentColor.h < targetColor.h)
				{
					currentColor.h += speed;
				}
				else if(currentColor.h > targetColor.h)
				{
					low = false;
					currentColor.h -= speed;
				}

				if (
					(low && currentColor.h > targetColor.h) ||
					(!low && currentColor.h < targetColor.h)
					)
				{
					currentColor.h = targetColor.h;
				}

				// Saturation
				low = true;
				if (currentColor.s < targetColor.s)
				{
					currentColor.s += speed;
				}
				else if(currentColor.s > targetColor.s)
				{
					low = false;
					currentColor.s -= speed;
				}

				if (
					(low && currentColor.s > targetColor.s) ||
					(!low && currentColor.s < targetColor.s)
					)
				{
					currentColor.s = targetColor.s;
				}

				// Value
				low = true;
				if (currentColor.l < targetColor.l)
				{
					currentColor.l += speed;
				}
				else if(currentColor.l > targetColor.l)
				{
					low = false;
					currentColor.l -= speed;
				}

				if (
					(low && currentColor.l > targetColor.l) ||
					(!low && currentColor.l < targetColor.l)
					)
				{
					currentColor.l = targetColor.l;
				}

				currentColor.Update(currentColor.h, currentColor.s, currentColor.l);
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