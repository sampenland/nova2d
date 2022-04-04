#pragma once
#include "SDL_mixer.h"

namespace novazero
{
	namespace utils
	{
		class AudioManager
		{

		private:

			bool m_Started = false;

		public:

			AudioManager();

			

			void DestroySelf();

		};
	}
}