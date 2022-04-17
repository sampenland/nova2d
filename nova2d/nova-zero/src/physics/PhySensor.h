#pragma once
#include <vector>
#include <string>
#include "box2d/box2d.h"
#include "../maths/Vec2.h"
#include "../core/Positional.h"
#include "../physics/PhyBase.h"

namespace novazero
{
	namespace physics
	{
		enum class Shapes
		{
			Rect,
			Poly,
			Circle
		};

		using namespace novazero::maths;
		using namespace novazero::core;

		class PhySensor :
			public PhyBase,
			public Positional
		{
		private:

			Shapes m_Shape = Shapes::Rect;

		public:

			// Rect
			PhySensor(std::string colliderName, bool staticBody, Vec2 position, Vec2 size, float density = 0.5f, float friction = 0.3f);
			
			// Poly
			PhySensor(std::string colliderName, bool staticBody, Vec2 position, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			
			// Circle
			PhySensor(std::string colliderName, bool staticBody,
				Vec2 position, float radius, float density = 0.5f, float friction = 0.3f);

			void DestroySelf();

		};
	}
}