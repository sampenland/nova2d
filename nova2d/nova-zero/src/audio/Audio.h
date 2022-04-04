#pragma once
#include "SDL_mixer.h"
#include <string>

namespace novazero
{
	namespace audio
	{
		class Audio
		{

		public:

			Audio() { };

			virtual void PlayOnce() = 0;
			virtual void Loop() = 0;
			virtual void Stop() = 0;
			virtual void Restart() = 0;

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
			void Restart() override;

			bool IsValid() override;

			void DestroySelf() override;

		};

		// --------------------------------------------------------------------------------

		class SoundEffect : public Audio
		{

		private:

			Mix_Chunk* m_SoundEffect = NULL;

		public:

			SoundEffect(const std::string& assetName, const std::string& assetPath);

			void PlayOnce() override;
			void Loop() override;
			void Stop() override;
			void Restart() override;

			bool IsValid() override;

			void DestroySelf() override;

		};
	}
}