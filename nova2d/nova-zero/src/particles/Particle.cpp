#include "Particle.h"
#include "../core/Game.h"

namespace novazero
{
	namespace particles
	{
        using namespace core;

        Particle::Particle(std::string assetName, int x, int y) : Deleteable("particle_")
        {
            m_ID = n2dGameGetID();
            m_DeleteName = "particle_" + std::to_string(m_ID);

            //Set offsets
            m_OffsetX = x - 5 + (rand() % 25);
            m_OffsetY = y - 5 + (rand() % 25);

            //Initialize animation
            m_CurrentFrame = rand() % 5;

            m_Texture = n2dAssetsGetTexture(assetName);

            if (!m_Texture)
            {
                DestroySelf();
                return;
            }

        }

        void Particle::Draw()
        {
            //m_Texture->Draw(m_OffsetX, m_OffsetY);
            m_CurrentFrame++;
        }

        void Particle::CheckIfDead()
        {
            if (m_CurrentFrame >= m_MaxFrames)
            {
                DestroySelf();
                return;
            }
        }

        void Particle::DestroySelf()
        {
            CleanUpdaters();
            
            m_DeleteNow = 1;
        }
	}
}