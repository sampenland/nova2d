#pragma once
#include "Graver.h"

#include <map>

namespace novazero
{
	namespace physics
	{
		class GraverManager
		{

		private:

			// int key = graver group and float value = force magnitude
			std::map<int, float> m_GraverMags;

		public:

			GraverManager();
			~GraverManager();

			void AddGraver(Graver* graver);
			void RemoveGraver(unsigned int id);

			void Update();
			void SumGroups();

		};
	}
}