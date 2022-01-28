#pragma once
#include <string>
#include <vector>

namespace novazero
{
	namespace core
	{
		class Deleteable
		{

		protected:

			Deleteable(std::string name);

			bool m_DeleteNow = 0;
			std::string m_DeleteName = "";

			std::vector<unsigned int> m_CleanUpdaters;
			void CleanUpdaters();

		public:

			virtual ~Deleteable() {};
			bool IsDeleted() { return m_DeleteNow; }
			void SetDeleted(bool v) { m_DeleteNow = v ? 1 : 0; }
		};
	}
}