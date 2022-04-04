#pragma once
#include "AudioManager.h"
#include "../logging/logging.h"
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		using namespace logging;
		using namespace core;

		AudioManager::AudioManager()
		{
			// load support for the OGG and MOD sample/music formats
			int flags = MIX_INIT_MP3 | MIX_INIT_OGG;
			int initted = Mix_Init(flags);
			if ((initted & flags) != flags) {

				std::string err = Mix_GetError();
				LOG(LVL_FATAL_ERROR, "Audio engine failed to start. Error: " + err);
			}
			else
			{
				LOG(LVL_CONFIRMATION, "Audio engine started.");
				m_Started = true;
			}

			if (!m_Started)
				return;
		}



		void AudioManager::DestroySelf()
		{
			if (m_Started)
			{
				while (Mix_Init(0))
					Mix_Quit();
			}
		}
	}
}