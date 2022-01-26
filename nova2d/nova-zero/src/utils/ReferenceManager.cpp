#include "ReferenceManager.h"

namespace novazero
{
	namespace utils
	{
		ReferenceManager::ReferenceManager()
		{

		}

		ReferenceManager::~ReferenceManager()
		{
			m_References.clear();
		}

		void ReferenceManager::AddReference(std::string name, Referenceable* ref)
		{
			m_References[name] = ref;
		}

		void ReferenceManager::RemoveReference(std::string name)
		{
			if (m_References.end() != m_References.find(name))
			{
				std::map<std::string, Referenceable*>::iterator f = m_References.find(name);
				m_References.erase(f);
			}
		}

		Referenceable* ReferenceManager::GetReferenced(std::string name)
		{
			try
			{
				return m_References.at(name);
			}
			catch (const std::out_of_range& oor)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot find game reference: " + name);
				LOG(LVL_NON_FATAL_ERROR, oor.what());
				return nullptr;
			}
		}
	}
}