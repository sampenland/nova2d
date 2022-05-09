#include "PhysicsDebug.h"
#include "../logging/logging.h"
#include "../graphics/gfx/SDL2_gfxPrimitives.h"
#include "../core/Game.h"
#include "../core/NovaCore.h"

namespace novazero
{
    namespace debug
    {
        using namespace novazero::core;

        PhysicsDebug::PhysicsDebug()
        {
            SetFlags(b2Draw::e_shapeBit | b2Draw::e_particleBit | b2Draw::e_aabbBit | b2Draw::e_centerOfMassBit |
                    b2Draw::e_jointBit);            
        }

        void PhysicsDebug::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            // TODO: stack allocate not heap (Fix)
            Sint16* vx = new Sint16[vertexCount];
            Sint16* vy = new Sint16[vertexCount];

            for (int i = 0; i < vertexCount; i++)
            {
                vx[i] = (Sint16)(vertices[i].x * PHYSICS_CONVERSION_FACTOR_MTP);
                vy[i] = (Sint16)(vertices[i].y * PHYSICS_CONVERSION_FACTOR_MTP);
            }

            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            filledPolygonRGBA(Game::s_Renderer->GetSDLRenderer(),
                vx,
                vy,
                (int)vertexCount,
                (Uint8)c.r,
                (Uint8)c.g,
                (Uint8)c.b,
                (Uint8)c.a
            );
        }
        
        void PhysicsDebug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            // TODO: stack allocate not heap (Fix)
            Sint16* vx = new Sint16[vertexCount];
            Sint16* vy = new Sint16[vertexCount];

            for (int i = 0; i < vertexCount; i++)
            {
                vx[i] = (Sint16)(vertices[i].x * PHYSICS_CONVERSION_FACTOR_MTP);
                vy[i] = (Sint16)(vertices[i].y * PHYSICS_CONVERSION_FACTOR_MTP);
            }

            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            filledPolygonRGBA(Game::s_Renderer->GetSDLRenderer(),
                vx,
                vy,
                (Sint16)vertexCount,
                (Uint8)c.r,
                (Uint8)c.g,
                (Uint8)c.b,
                (Uint8)c.a
            );
        }
        
        void PhysicsDebug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            circleRGBA(Game::s_Renderer->GetSDLRenderer(),
                (Sint16)(center.x * PHYSICS_CONVERSION_FACTOR_MTP),
                (Sint16)(center.y * PHYSICS_CONVERSION_FACTOR_MTP),
                (Sint16)(radius * PHYSICS_CONVERSION_FACTOR_MTP),
                (Uint8)c.r,
                (Uint8)c.g,
                (Uint8)c.b,
                (Uint8)c.a
            );
        }
        
        void PhysicsDebug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(),
                (Sint16)(center.x * PHYSICS_CONVERSION_FACTOR_MTP),
                (Sint16)(center.y * PHYSICS_CONVERSION_FACTOR_MTP),
                (Sint16)(radius * PHYSICS_CONVERSION_FACTOR_MTP),
                (Uint8)c.r,
                (Uint8)c.g,
                (Uint8)c.b,
                (Uint8)c.a
            );
        }
        
        void PhysicsDebug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            lineRGBA(Game::s_Renderer->GetSDLRenderer(),
                (Sint16)p1.x * PHYSICS_CONVERSION_FACTOR_MTP, (Sint16)p1.y * PHYSICS_CONVERSION_FACTOR_MTP,
                (Sint16)p2.x * PHYSICS_CONVERSION_FACTOR_MTP, (Sint16)p2.y * PHYSICS_CONVERSION_FACTOR_MTP,
                (Uint8)c.r,
                (Uint8)c.g,
                (Uint8)c.b,
                (Uint8)c.a
            );
        }
        
        void PhysicsDebug::DrawTransform(const b2Transform& xf)
        {
            int i = 0;
        }

        void PhysicsDebug::DrawParticles(const b2Vec2* centers, float32 radius, const b2ParticleColor* colors, int32 count)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;

            for(int32 i = 0; i < count; i++)
            {
                filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(),
                    (Sint16)(centers[i].x * PHYSICS_CONVERSION_FACTOR_MTP),
                    (Sint16)(centers[i].y * PHYSICS_CONVERSION_FACTOR_MTP),
                    (Sint16)(radius * PHYSICS_CONVERSION_FACTOR_MTP),
                    (Uint8)c.r,
                    (Uint8)c.g,
                    (Uint8)c.b,
                    (Uint8)c.a
                );
            }
        }
    }
}