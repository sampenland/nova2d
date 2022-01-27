#pragma once
#include "../core/Deleteable.h"
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;
		using namespace maths;

		class Graver : public Deleteable
		{

		private:

			unsigned int m_CleanID = 0;

		public:

			unsigned int m_ID = 0;
			int m_GraverEffectRadius = 2;
			int m_GraverGroupKeyID;
			Vec2Int m_GraverEffectMagnitude;

		public:

			Graver(int graverGroup, int effectRadius, Vec2Int defaultGraverEffectMag);
			~Graver();

			void GraverUpdate();
			void DestroySelf();

		};
	}
}