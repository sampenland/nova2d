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

			void AddReference(const std::string& name, Referenceable* object);
			void RemoveReference(const std::string& name);

			Referenceable* GetReferenced(const std::string& name);
			unsigned int GetReferenceCount() { return (unsigned int)m_References.size(); }

		};
	}
}