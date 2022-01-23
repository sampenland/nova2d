#pragma once
#include <string>
#include <vector>

namespace novazero
{
	namespace core
	{
		class Deleteable
		{

		public:

			Deleteable(std::string name);
			virtual ~Deleteable() {};

			bool m_DeleteNow = 0;
			std::string m_DeleteName = "";

			std::vector<unsigned int> m_CleanUpdaters;
			void CleanUpdaters();
		};
	}
}