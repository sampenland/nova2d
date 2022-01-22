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

			bool m_DeleteNow = false;
			std::string m_DeleteName = "";

			virtual void Update() = 0;

			std::vector<unsigned int> m_CleanUpdaters;
			void CleanUpdaters();
		};
	}
}