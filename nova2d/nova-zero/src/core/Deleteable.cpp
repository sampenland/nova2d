#include "Deleteable.h"
#include "Game.h"
#include "../logging/logging.h"

namespace novazero
{
	namespace core
	{
		using namespace logging;

		Deleteable::Deleteable(const std::string& name)
			: m_DeleteName(name)
		{
			 
		}

		void Deleteable::CleanUpdaters()
		{
			for (size_t i = 0; i < m_CleanUpdaters.size(); i++)
			{
				n2dRemoveUpdater(m_CleanUpdaters[i]);
			}

			m_CleanUpdaters.clear();
		}
	}
}