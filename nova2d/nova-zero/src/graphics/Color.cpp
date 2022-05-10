#include "Color.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		Color::Color()
		{
			r = 255;
			g = 255;
			b = 255;
			a = 255;

			// Create HSL color as well
			HSLUpdate();

		}

		int* Color::GetRRef() { return (int*)&r; }
		int* Color::GetGef() { return (int*)&g; }
		int* Color::GetBRef() { return (int*)&b; }
		int* Color::GetARef() { return (int*)&a; }

		float* Color::GetHRef() { return &h; }
		float* Color::GetSRef() { return &s; }
		float* Color::GetLRef() { return &l; }

		Color::Color(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;

			// Create HSL color as well
			HSLUpdate();
		}

		void Color::RGBUpdate()
		{
			Update(this->h, this->s, this->l);
		}

		void Color::HSLUpdate()
		{
			Update(this->r, this->g, this->b);
		}

		void Color::Update(float h, float s, float l)
		{
			// Create HSL color as well
			Uint8 rgb[3];
			HSL2RGB(h, s, l, rgb);
			this->r = rgb[0];
			this->g = rgb[1];
			this->b = rgb[2];
		}

		void Color::Update(Uint8 r, Uint8 g, Uint8 b)
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
		void Color::HSL2RGB(float h, float s, float l, Uint8 outRGB[3])
		{
			h *= 360.f;

			if (h > 360 || h < 0 || s > 1.f || s < 0.f || l > 1.f || l < 0.f) {
				LOG(LVL_NFE, "Could not conver HSL to RGB", __FILE__, __LINE__);
				return;
			}

			float C = s * l;
			float X = C * (1 - std::abs(std::fmod(h / 60.0, 2) - 1));
			float m = l - C;
			float rr, gg, bb;
			if (h >= 0 && h < 60) {
				rr = C;
				gg = X;
				bb = 0;
			}
			else if (h >= 60 && h < 120) {
				rr = X;
				gg = C;
				bb = 0;
			}
			else if (h >= 120 && h < 180) {
				rr = 0;
				gg = C;
				bb = X;
			}
			else if (h >= 180 && h < 240) {
				rr = 0;
				gg = X;
				bb = C;
			}
			else if (h >= 240 && h < 300) {
				rr = X;
				gg = 0;
				bb = C;
			}
			else {
				rr = C;
				gg = 0;
				bb = X;
			}

			outRGB[0] = (Uint8)((rr + m) * 255);
			outRGB[1] = (Uint8)((gg + m) * 255);
			outRGB[2] = (Uint8)((bb + m) * 255);

		}

		/*
			outHSL is a pointer to value (HSL will be returned in this)
		*/
		void Color::RGB2HSL(Uint8 red, Uint8 green, Uint8 blue, float outHSL[3])
		{
			float rr = red / 255.f;
			float gg = green / 255.f;
			float bb = blue / 255.f;

			float max = std::max(std::max(rr, gg), bb);
			float min = std::max(std::min(rr, gg), bb);

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
				float d = max - min;

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
			Transition from color A to B at speed T and ouput to Out
		*/
		void Color::Interpolate(Color a, Color b, float t, Color& out)
		{
			// Hue interpolation
			float h;
			float d = b.h - a.h;
			if (a.h > b.h)
			{
				// Swap (a.h, b.h)
				float h3 = b.h;
				b.h = a.h;
				a.h = h3;
				d = -d;
			}

			if (d > 0.5) // 180deg
			{
				a.h = a.h + 1; // 360deg
				h = (float)std::fmod((a.h + t * (b.h - a.h)), 1.0); // 360deg
			}

			if (d <= 0.5) // 180deg
			{
				h = a.h + t * d;
			}

			out.h = h;

			float s = a.s + t * (b.s - a.s);
			float l = a.l + t * (b.l - a.l);
			out.s = s;
			out.l = l;

			out.RGBUpdate();

		}

		Vec4 Color::GetNormalized() const
		{
			Vec4 norm((float)r / 255, (float)g / 255, (float)b / 255, (float)a / 255);
			return norm;
		}

		bool Color::operator==(const Color& other)
		{
			return r == other.r && g == other.g && b == other.b && a == other.a;
		}

		bool Color::operator!=(const Color& other)
		{
			return !(*this == other);
		}

		std::ostream& operator<<(std::ostream& stream, const Color& color)
		{
			stream << "Color: [" << std::to_string(color.r) << ", " << std::to_string(color.g) <<
				", " << std::to_string(color.b) << ", " << std::to_string(color.a) << "] [" <<
				std::to_string(color.h) << ", " << std::to_string(color.s) << ", " << std::to_string(color.l) << "]";
			return stream;
		}
	}
}