#pragma once
#include <iostream>
#include "../maths/Vec4.h"
#include <SDL_stdinc.h>
#include <string>

namespace novazero
{
	namespace graphics
	{
		using namespace maths;

		struct Color
		{
			Uint8 r, g, b, a;
			float h, s, l;

			Color();

			int* GetRRef();
			int* GetGef();
			int* GetBRef();
			int* GetARef();

			float* GetHRef();
			float* GetSRef();
			float* GetLRef();

			Color(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);

			void RGBUpdate();

			void HSLUpdate();

			void Update(float h, float s, float l);

			void Update(Uint8 r, Uint8 g, Uint8 b);

			/*
				outRGB is a pointer to value (RGB will be returned in this)
			*/
			void HSL2RGB(float h, float s, float l, Uint8 outRGB[3]);

			/*
				outHSL is a pointer to value (HSL will be returned in this)
			*/
			void RGB2HSL(Uint8 red, Uint8 green, Uint8 blue, float outHSL[3]);

			/*
				Transition from color A to B at speed T and ouput to Out
			*/
			static void Interpolate(Color a, Color b, float t, Color& out);

			Vec4 GetNormalized() const;

			bool operator==(const Color& other);

			bool operator!=(const Color& other);

			friend std::ostream& operator<<(std::ostream& stream, const Color& color);

		};
	}
}