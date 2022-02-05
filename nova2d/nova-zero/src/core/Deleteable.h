#pragma once
#include <string>
#include <vector>

namespace novazero
{
	namespace core
	{
		class Deleteable
		{

		private:

			bool m_Enabled = true;

		protected:

			Deleteable(std::string name);

			bool m_DeleteNow = 0;
			std::string m_DeleteName = "";

			std::vector<unsigned int> m_CleanUpdaters;
			void CleanUpdaters();

		public:

			virtual ~Deleteable() {};
			bool IsDeleted() { return m_DeleteNow == 1; }
			void SetDeleted(bool v) { m_DeleteNow = v ? 1 : 0; }

			void SetEnabled(bool v) { m_Enabled = v; } //TODO: crash here
			bool IsEnabled() { return m_Enabled; }

		};
	}
}