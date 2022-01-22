#pragma once

namespace novazero
{
	namespace core
	{
		class Destructor
		{

		protected:
			
			Destructor() {};
		
		public:

			bool m_Dead = false;
		
			~Destructor() {};
		};
	}
}