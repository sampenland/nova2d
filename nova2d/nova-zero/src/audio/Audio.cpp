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
				LOG(LVL_NFE, "Failed to load music: " + assetName + ". Error: " + err);
				return;
			}
		}

		void Music::PlayOnce()
		{

		}

		void Music::Loop()
		{

		}

		void Music::Stop()
		{

		}

		void Music::Restart()
		{

		}

		bool Music::IsValid()
		{
			if (!m_Music) return false;
			return true;
		}

		void Music::DestroySelf()
		{

		}
		
		// ------------------------------------------------------------------------------

		SoundEffect::SoundEffect(const std::string& assetName, const std::string& assetPath)
		{
			m_SoundEffect = Mix_LoadWAV(assetPath.c_str());

			if (!m_SoundEffect)
			{
				std::string err = Mix_GetError();
				LOG(LVL_NFE, "Failed to load sound effect: " + assetName + ". Error: " + err);
				return;
			}
		}

		void SoundEffect::PlayOnce()
		{

		}

		void SoundEffect::Loop()
		{

		}

		void SoundEffect::Stop()
		{

		}

		void SoundEffect::Restart()
		{

		}

		bool SoundEffect::IsValid()
		{
			if (!m_SoundEffect) return false;
			return true;
		}

		void SoundEffect::DestroySelf()
		{

		}
	}
}