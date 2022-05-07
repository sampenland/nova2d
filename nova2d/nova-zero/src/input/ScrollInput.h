#pragma once
#include <string>
#include "SDL.h"
#include "Box2D/Box2D.h"

namespace novazero
{
	namespace input
	{
		class ScrollInput
		{

		private:

			std::string m_Title = "";
			float* m_ValueF = nullptr;
			float m_MinF = 0.f;
			float m_MaxF = 1.f;

			Uint8* m_ValueI = nullptr;
			Uint8 m_MinI = 0;
			Uint8 m_MaxI = 255;

			int32* m_ValueI32 = nullptr;
			int32 m_MinI32 = 0;
			int32 m_MaxI32 = 255;

			bool m_IsFloat = true;
			bool m_IsI32 = false;

		public:

			ScrollInput(const std::string& title, float min, float max, float* value);
			ScrollInput(const std::string& title, Uint8 min, Uint8 max, Uint8* value);
			ScrollInput(const std::string& title, int32 min, int32 max, int32* value);

			Uint8 GetValueI() const;
			float GetValueF() const;

			void Draw();

			void DestroySelf();
		};
	}
}