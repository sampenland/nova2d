#pragma once

namespace novazero
{
	namespace physics
	{
		class Graver
		{

		private:

			int m_GraverGroupKeyID;
			unsigned int m_ID = 0;

		public:

			Graver(int graverGroup);
			~Graver();

			void GraverUpdate();

		};
	}
}