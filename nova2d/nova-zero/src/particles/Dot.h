#pragma once
#include "Particle.h"

namespace novazero
{
    namespace particles
    {
        using namespace core;

        class Dot
        {

        private:
            
            Particle* particles[MAX_PARTICLES];

            void DrawParticles();

            int m_OffsetX = 0;
            int m_OffsetY = 0;

            int m_VelocityX = 0;
            int m_VelocityY = 0;

        public:
            

            static const int DOT_WIDTH = 16;
            static const int DOT_HEIGHT = 16;

            static const int DOT_MAX_VEL = 10;

            Dot();

            void DestroySelf();
            void Move();
            void Draw();

        };
    }
}