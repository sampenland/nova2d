#pragma once
#include "SDL_mixer.h"
#include <string>

namespace novazero
{
	namespace audio
	{
		class Audio
		{

		private:

			int m_Volumn = 100;

		public:

			Audio() { };

			virtual void PlayOnce() = 0;
			virtual void Loop() = 0;
			virtual void Stop() = 0;

			virtual void SetVolume(int volume) = 0;

			virtual bool IsValid() = 0;

			virtual void DestroySelf() = 0;

		protected:

			bool m_Loop = false;
			bool m_Playing = false;
			std::string m_AssetName = "";

		};

		class Music : public Audio
		{

		private:

			//The music that will be played
			Mix_Music* m_Music = NULL;
			
		public:

			Music(const std::string& assetName, const std::string& assetPath);

			void PlayOnce() override;
			void Loop() override;
			void Stop() override;

			void SetVolume(int volume) override;

			bool IsValid() override;

			void DestroySelf() override;

		};

		// --------------------------------------------------------------------------------

		class SoundEffect : public Audio
		{

		private:

			Mix_Chunk* m_SoundEffect = NULL;
			int m_Channel = -1;

		public:

			SoundEffect(const std::string& assetName, const std::string& assetPath);

			void PlayOnce() override;
			void Loop() override;
			void Stop() override;
			void Resume();
			void Pause();

			void SetVolume(int volume) override;

			bool IsValid() override;

			void DestroySelf() override;

		public:

			static void StopAllSoundEffects();

		};
	}
}