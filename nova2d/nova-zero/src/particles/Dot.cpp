#include "Dot.h"

namespace novazero
{
	namespace particles
	{
        Dot::Dot()
        {
            m_OffsetX = 0;
            m_OffsetY = 0;

            m_VelocityX = 0;
            m_VelocityY = 0;

            for (int i = 0; i < MAX_PARTICLES; ++i)
            {
                particles[i] = new Particle("player", m_OffsetX, m_OffsetY);
            }
        }

        void Dot::Draw()
        {
            //Show the dot
            //gDotTexture.render(m_OffsetX, m_OffsetY);

            //Show particles on top of dot
            DrawParticles();
        }

        void Dot::DrawParticles()
        {
            //Go through particles
            for (int i = 0; i < MAX_PARTICLES; ++i)
            {
                //Delete and replace dead particles
                particles[i]->CheckIfDead();
                if (particles[i]->IsDeleted())
                {
                    delete particles[i];
                    particles[i] = new Particle("player", m_OffsetX, m_OffsetY);
                }
            }

            //Show particles
            for (int i = 0; i < MAX_PARTICLES; ++i)
            {
                particles[i]->Draw();
            }
        }
	}
}
