#pragma once
#include "../core/Deleteable.h"
#include <string>

#include "SDL.h"

namespace novazero
{
	namespace particles
	{
        using namespace core;

        class Particle :
            public Deleteable
        {

        private:
            
            int m_OffsetX = 0;
            int m_OffsetY = 0;

            int m_CurrentFrame;
            int m_MaxFrames = 0;

            SDL_Texture* m_Texture;

        public:

            unsigned int m_ID = 0;
            Particle(std::string assetName, int x, int y);

            void Draw();
            void CheckIfDead();

            void DestroySelf();

        };
	}
}