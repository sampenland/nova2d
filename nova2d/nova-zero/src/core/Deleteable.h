#pragma once

namespace novazero
{
	namespace core
	{
		class Deleteable
		{

		public:

			Deleteable();

			bool m_DeleteNow = false;
			virtual void Update() = 0;
		};
	}
}