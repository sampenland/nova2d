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

			unsigned int m_ID = 0;

			Shapes m_Shape = Shapes::Rect;

			b2Body* m_Body = nullptr;

			Vec2 m_PhySize = Vec2(0, 0);
			float m_Radius = 1.f;

			b2FixtureDef fixtureDef;
			float m_Density = 1.f;
			float m_Friction = 1.f;
			bool m_IsSensor = 1.f;
			float m_Restitution = 1.f;
			float m_RestitutionThres = 1.f;

		public:

			// Rect
			PhySensor(std::string colliderName, bool staticBody, Vec2 position, Vec2 size, float density = 0.5f, float friction = 0.3f);
			
			// Poly
			PhySensor(std::string colliderName, bool staticBody, Vec2 position, std::vector<Vec2> shapeVertices, const int vertexCount, float density = 0.5f, float friction = 0.3f);
			
			// Circle
			PhySensor(std::string colliderName, bool staticBody,
				Vec2 position, float radius, float density = 0.5f, float friction = 0.3f);
			
			unsigned int GetPhyID() const override;

			void DestroySelf();

		};
	}
}