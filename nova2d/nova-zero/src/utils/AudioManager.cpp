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

		AudioManager::AudioManager(unsigned int maxChannels)
		{
			// Support only OGG files
			int flags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_MID;
			int initted = Mix_Init(flags);
			if ((initted & flags) != flags) {

				std::string err = Mix_GetError();
				LOG(LVL_FATAL_ERROR, "Audio engine failed to start. Error: " + err);
				return;
			}

			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) 
			{
				std::string err = Mix_GetError();
				LOG(LVL_FATAL_ERROR, "Audio engine failed to open device. Error: " + err);
				return;
			}

			LOG(LVL_CONFIRMATION, "Audio engine started. Supporting: ogg, mp3, midi");
			Mix_AllocateChannels((int)maxChannels);
			m_Started = true;

		}

		Music* AudioManager::LoadAndAddMusic(const std::string& assetName, const std::string& assetPath)
		{
			if (
				assetPath.find(".wav") == std::string::npos &&
				assetPath.find(".ogg") == std::string::npos &&
				assetPath.find(".mp3") == std::string::npos &&
				assetPath.find(".midi") == std::string::npos
				)
			{
				LOG(LVL_NFE, assetPath + " <- incorect file type. Supported: wav, ogg, mp3, midi");
				return nullptr;
			}

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
			if (
				assetPath.find(".wav") == std::string::npos &&
				assetPath.find(".ogg") == std::string::npos
				)
			{
				LOG(LVL_NFE, assetPath + " <- incorect file type. Supported: wav, ogg");
				return nullptr;
			}

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