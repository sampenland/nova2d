#include "Deleteable.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		Deleteable::Deleteable()
		{
			Game::s_SceneManager->AddDeleteable(this);
		}
	}
}