#pragma once
#include "../core/Referenceable.h"
#include <string>
#include <map>
#include <stdexcept>
#include "../logging/logging.h"

namespace novazero
{
	namespace utils
	{
		using namespace core;

		class ReferenceManager
		{
		private:

			std::map<std::string, Referenceable*> m_References = {};

		public:

			ReferenceManager();
			~ReferenceManager();

			void AddReference(std::string name, Referenceable* object);
			void RemoveReference(std::string name);

			Referenceable* GetReferenced(std::string name);

		};
	}
}