#include "Deleteable.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Deleteable::Deleteable(std::string name)
			: m_DeleteName(name)
		{
			Game::s_SceneManager->AddDeleteable(this);
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