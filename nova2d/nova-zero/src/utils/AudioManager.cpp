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
				return;
			}
			else
			{
				LOG(LVL_CONFIRMATION, "Audio engine started.");
			}

			// open 44.1KHz, signed 16bit, system byte order,
			//      stereo audio, using 1024 byte chunks
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) 
			{
				std::string err = Mix_GetError();
				LOG(LVL_FATAL_ERROR, "Audio engine failed to open device. Error: " + err);
				return;
			}

			m_Started = true;

		}

		Music* AudioManager::LoadAndAddMusic(const std::string& assetName, const std::string& assetPath)
		{
			Music* m = new Music(assetName, assetPath);

			if (!m->IsValid())
			{
				LOG(LVL_NFE, "Failed to add music to manager: " + assetName);
				delete m;
				return nullptr;
			}

			m_Musics[assetName] = m;

			return m_Musics[assetName];
		}

		SoundEffect* AudioManager::LoadAndAddSoundEffect(const std::string& assetName, const std::string& assetPath)
		{
			SoundEffect* se = new SoundEffect(assetName, assetPath);

			if (!se->IsValid())
			{
				LOG(LVL_NFE, "Failed to add sound effect to manager: " + assetName);
				delete se;
				return nullptr;
			}

			m_SoundEffects[assetName] = se;

			return m_SoundEffects[assetName];
		}

		bool AudioManager::AudioExists(bool isMusic, const std::string& assetName)
		{
			if (isMusic)
			{
				if (m_Musics.find(assetName) != m_Musics.end())
				{
					return true;
				}
				else
				{
					LOG(LVL_NFE, "Music: " + assetName + " does not exists.");
				}
			}
			else
			{
				if (m_SoundEffects.find(assetName) != m_SoundEffects.end())
				{
					return true;
				}
				else
				{
					LOG(LVL_NFE, "Sound Effect: " + assetName + " does not exists.");
				}
			}

			return false;
		}

		void AudioManager::PlayOnce(bool isMusic, const std::string& assetName)
		{
			if (!AudioExists(isMusic, assetName)) return;

			if (isMusic)
			{
				m_Musics[assetName]->PlayOnce();
			}
			else
			{
				m_SoundEffects[assetName]->PlayOnce();
			}
		}

		void AudioManager::Loop(bool isMusic, const std::string& assetName)
		{
			if (!AudioExists(isMusic, assetName)) return;

			if (isMusic)
			{
				m_Musics[assetName]->Loop();
			}
			else
			{
				m_SoundEffects[assetName]->Loop();
			}
		}

		void AudioManager::Stop(bool isMusic, const std::string& assetName)
		{
			if (!AudioExists(isMusic, assetName)) return;

			if (isMusic)
			{
				m_Musics[assetName]->Stop();
			}
			else
			{
				m_SoundEffects[assetName]->Stop();
			}
		}

		void AudioManager::Restart(bool isMusic, const std::string& assetName, bool loop)
		{
			if (!AudioExists(isMusic, assetName)) return;

			if (isMusic)
			{
				m_Musics[assetName]->Restart();
			}
			else
			{
				m_SoundEffects[assetName]->Restart();
			}
		}

		void AudioManager::DestroySelf()
		{
			if (m_Started)
			{
				Mix_CloseAudio();
				while (Mix_Init(0))
					Mix_Quit();
			}

			for (auto i = m_Musics.begin(); i != m_Musics.end(); i++)
			{
				i->second->DestroySelf();
			}

			for (auto i = m_SoundEffects.begin(); i != m_SoundEffects.end(); i++)
			{
				i->second->DestroySelf();
			}
		}
	}
}