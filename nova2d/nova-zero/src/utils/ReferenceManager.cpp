#include "ReferenceManager.h"
#include <vector>
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		using namespace novazero::core;

		ReferenceManager::ReferenceManager()
		{

		}

		ReferenceManager::~ReferenceManager()
		{
			m_References.clear();
		}

		void ReferenceManager::AddReference(const std::string& name, void* object, const std::string& groupName)
		{
			Reference* ref = new Reference(object, groupName);
			m_References[name] = ref;
		}

		void ReferenceManager::RemoveReference(const std::string& name)
		{
			if (m_References.end() != m_References.find(name))
			{
				std::map<std::string, Reference*>::iterator f = m_References.find(name);
				m_References.erase(f);
			}
		}

		void* ReferenceManager::GetRandomReferenceInGroup(const std::string& groupName)
		{
			std::vector<void*> m_Possibles;
			for (auto it : m_References)
			{
				if (it.second->m_Group == groupName)
				{
					m_Possibles.push_back(it.second->m_Ref);
				}
			}

			int rnd = n2dRandomInt(0, m_Possibles.size() - 1);
			return m_Possibles[rnd];
		}

		void* ReferenceManager::GetReferenced(const std::string& name)
		{
			try
			{
				return m_References.at(name)->m_Ref;
			}
			catch (const std::out_of_range& oor)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot find game reference: " + name, __FILE__, __LINE__);
				LOG(LVL_NON_FATAL_ERROR, oor.what(), __FILE__, __LINE__);
				return nullptr;
			}
		}
	}
}