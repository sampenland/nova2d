#pragma once

namespace novazero
{
	namespace core
	{
		class Removeable
		{

		protected:

			Removeable() {};
			
		public:

			~Removeable() {};

			bool m_Alive = true;
			bool m_Destroyed = false;

			virtual bool CheckAlive() = 0;
			virtual void DestroySelf() = 0;

		};
	}
}