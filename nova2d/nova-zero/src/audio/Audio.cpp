#include "Audio.h"
#include "../core/Game.h"

namespace novazero
{
	namespace audio
	{
		using namespace core;

		Music::Music(const std::string& assetName, const std::string& assetPath)
		{
			m_Music = Mix_LoadMUS(assetPath.c_str());

			if (!m_Music)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to load music: " + assetName + ". Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void Music::PlayOnce()
		{
			if (!m_Music)
			{
				LOG(LVL_WARNING, "Couldn't play music: music not loaded properly.", __FILE__, __LINE__);
				return;
			}

			if (Mix_PlayMusic(m_Music, 0) == -1)
			{
				std::string err = Mix_GetError();
				LOG(LVL_WARNING, "Music failed to place. Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void Music::Loop()
		{
			if (!m_Music)
			{
				LOG(LVL_WARNING, "Couldn't play music: music not loaded properly.", __FILE__, __LINE__);
				return;
			}

			if (Mix_PlayMusic(m_Music, -1) == -1) 
			{
				std::string err = Mix_GetError();
				LOG(LVL_WARNING, "Music failed to place. Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void Music::Stop()
		{
			if (!m_Music)
			{
				LOG(LVL_WARNING, "Couldn't stop music: music not loaded properly.", __FILE__, __LINE__);
				return;
			}

			Mix_HaltMusic();
		}

		bool Music::IsValid()
		{
			if (!m_Music) return false;
			return true;
		}

		void Music::SetVolume(int volume)
		{
			Mix_VolumeMusic(volume);
		}

		void Music::DestroySelf()
		{
			Mix_FreeMusic(m_Music);
			m_Music = NULL;
		}
		
		// ------------------------------------------------------------------------------

		SoundEffect::SoundEffect(const std::string& assetName, const std::string& assetPath)
		{
			m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

			if (!m_SoundEffect)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to load sound effect: " + assetName + ". Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void SoundEffect::PlayOnce()
		{
			if (!m_SoundEffect)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to play sound effect. Error: " + err, __FILE__, __LINE__);
				return;
			}

			m_Channel = Mix_PlayChannel(-1, m_SoundEffect, 0);
			if (m_Channel == -1)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to play sound effect. Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void SoundEffect::Loop()
		{
			if (!m_SoundEffect)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to play sound effect. Error: " + err, __FILE__, __LINE__);
				return;
			}

			m_Channel = Mix_PlayChannel(-1, m_SoundEffect, -1);
			if (m_Channel == -1) 
			{

				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to play sound effect. Error: " + err, __FILE__, __LINE__);
				return;
			}
		}

		void SoundEffect::SetVolume(int vol)
		{
			Mix_Volume(m_Channel, vol);
		}

		void SoundEffect::Pause()
		{
			if (m_Channel == -1) return;
			Mix_Pause(m_Channel);
		}

		void SoundEffect::Resume()
		{
			if (m_Channel == -1) return;
			Mix_Resume(m_Channel);
		}

		void SoundEffect::Stop()
		{
			if (m_Channel == -1) return;
			Mix_HaltChannel(m_Channel);
		}

		bool SoundEffect::IsValid()
		{
			if (!m_SoundEffect) return false;
			return true;
		}

		void SoundEffect::StopAllSoundEffects()
		{
			Mix_HaltChannel(-1);
		}

		void SoundEffect::DestroySelf()
		{
			Mix_FreeChunk(m_SoundEffect);
			m_SoundEffect = NULL;
		}
	}
}