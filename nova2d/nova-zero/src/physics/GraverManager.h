#pragma once
#include "Graver.h"

#include <map>
#include <vector>

namespace novazero
{
	namespace physics
	{
		class GraverManager
		{

		private:

			std::vector<Graver*> m_AllGravers;

			// int key = graver group and float value = force magnitude
			std::map<int, Vec2Int> m_GraverMags;

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