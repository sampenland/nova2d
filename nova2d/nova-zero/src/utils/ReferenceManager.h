#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include "../logging/logging.h"

namespace novazero
{
	namespace utils
	{
		class ReferenceManager
		{
		private:

			std::map<std::string, void*> m_References = {};

		public:

			ReferenceManager();
			~ReferenceManager();

			void AddReference(const std::string& name, void* object);
			void RemoveReference(const std::string& name);

			void* GetReferenced(const std::string& name);
			unsigned int GetReferenceCount() { return (unsigned int)m_References.size(); }

		};
	}
}