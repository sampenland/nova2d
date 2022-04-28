#pragma once
#include <string>
#include <map>
#include <stdexcept>
#include "../logging/logging.h"
#include <vector>

namespace novazero
{
	namespace utils
	{
		class Reference
		{

		public:

			void* m_Ref;
			std::string m_Group;
			
			Reference(void* ref, const std::string& groupName) : m_Ref(ref), m_Group(groupName) {};
		};

		class ReferenceManager
		{
		private:

			std::map<std::string, Reference*> m_References = {};

		public:

			ReferenceManager();
			~ReferenceManager();

			void AddReference(const std::string& name, void* object, const std::string& groupName = "all");
			void RemoveReference(const std::string& name);

			void* GetReferenced(const std::string& name);
			void* GetRandomReferenceInGroup(const std::string& groupName);
			unsigned int GetReferenceCount() { return (unsigned int)m_References.size(); }

		};
	}
}