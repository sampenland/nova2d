#include "PhysicsDebug.h"
#include "../logging/logging.h"
#include "../graphics/gfx/SDL2_gfxPrimitives.h"
#include "../core/Game.h"

namespace novazero
{
    namespace debug
    {
        PhysicsDebug::PhysicsDebug()
        {
            SetFlags(b2Draw::e_shapeBit);
        }

        void PhysicsDebug::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            // TODO: stack allocate not heap (Fix)
            Sint16* vx = new Sint16[vertexCount];
            Sint16* vy = new Sint16[vertexCount];

            for (int i = 0; i < vertexCount; i++)
            {
                vx[i] = vertices[i].x;
                vy[i] = vertices[i].y;
            }

            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            polygonColor(Game::s_Renderer->GetSDLRenderer(),
                vx,
                vy,
                (int)vertexCount,
                0x00FF00FF
            );
        }
        
        void PhysicsDebug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            // TODO: stack allocate not heap (Fix)
            Sint16* vx = new Sint16[vertexCount];
            Sint16* vy = new Sint16[vertexCount];

            for (int i = 0; i < vertexCount; i++)
            {
                vx[i] = vertices[i].x;
                vy[i] = vertices[i].y;
            }

            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            filledPolygonRGBA(Game::s_Renderer->GetSDLRenderer(),
                vx,
                vy,
                (int)vertexCount,
                c.r,
                c.g,
                c.b,
                c.a
            );
        }
        
        void PhysicsDebug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
        {
            circleRGBA(Game::s_Renderer->GetSDLRenderer(),
                center.x, center.y,
                radius,
                color.r,
                color.g,
                color.b,
                color.a
            );
        }
        
        void PhysicsDebug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            filledCircleRGBA(Game::s_Renderer->GetSDLRenderer(),
                center.x, center.y,
                radius,
                c.r,
                c.g,
                c.b,
                c.a
            );
        }
        
        void PhysicsDebug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            Color& c = *Game::s_Renderer->s_DebugRenderColor;
            lineRGBA(Game::s_Renderer->GetSDLRenderer(),
                p1.x, p1.y,
                p2.x, p2.y,
                c.r, c.g, c.b, c.a);
        }
        
        void PhysicsDebug::DrawTransform(const b2Transform& xf)
        {
            int i = 0;
        }

        void PhysicsDebug::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
        {
            
        }
    }
}