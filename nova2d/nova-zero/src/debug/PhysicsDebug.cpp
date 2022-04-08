#include "PhysicsDebug.h"
#include "../logging/logging.h"

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
            int i = 0;
        }
        
        void PhysicsDebug::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
        {
            int i = 0;
        }
        
        void PhysicsDebug::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
        {
            int i = 0;
        }
        
        void PhysicsDebug::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
        {
            int i = 0;
        }
        
        void PhysicsDebug::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
        {
            int i = 0;
        }
        
        void PhysicsDebug::DrawTransform(const b2Transform& xf)
        {
            int i = 0;
        }

        void PhysicsDebug::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
        {
            int i = 0;
        }
    }
}