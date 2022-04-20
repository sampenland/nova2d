#pragma once
#ifdef NOVA_ENSCRIPTEN
	#include <SDL2/SDL_mixer.h>
#else
	#include "SDL_mixer.h"
#endif

#include <string>
#include <map>
#include "../audio/Audio.h"

namespace novazero
{
	namespace utils
	{
		using namespace audio;

		class AudioManager
		{

		private:

			bool m_Started = false;

			std::map<std::string, Music*> m_Musics;
			std::map<std::string, SoundEffect*> m_SoundEffects;

		public:

			AudioManager(unsigned int maxChannels = 20);

			Music* LoadAndAddMusic(const std::string& assetName, const std::string& assetPath);
			SoundEffect* LoadAndAddSoundEffect(const std::string& assetName, const std::string& assetPath);

			bool AudioExists(bool isMusic, const std::string& assetName);

			void PlayOnce(bool isMusic, const std::string& assetName);
			void Loop(bool isMusic, const std::string& assetName);
			void Stop(bool isMusic, const std::string& assetName);
			void Restart(bool isMusic, const std::string& assetName, bool loop = false);

			void DestroySelf();

		};
	}
}