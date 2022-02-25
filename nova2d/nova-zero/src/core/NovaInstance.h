#pragma once
#include "../maths/Vec2.h"

namespace novazero
{
	namespace core
	{
		using namespace maths;

		class NovaInstance
		{

		protected:
			
			NovaInstance() {};

		public:

			virtual void CreateInstance(Vec2 position) = 0;

		};
	}
}