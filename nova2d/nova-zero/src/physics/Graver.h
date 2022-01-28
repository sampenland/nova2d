#pragma once
#include "../core/Deleteable.h"
#include "../maths/Vec2Int.h"
#include "../core/BoundUser.h"
#include "../graphics/Sprite.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		enum GraverType
		{
			Implosion,
			Explosion,
			Vec2Force
		};

		class Graver : 
			public Deleteable,
			public BoundUser
		{

		private:

			unsigned int m_CleanID = 0;

		public:

			unsigned int m_ID = 0;
			int m_GraverEffectRadius = 2;
			int m_GraverGroupKeyID;
			Vec2Int m_GraverEffectMagnitude;
			GraverType m_GraverType = GraverType::Vec2Force;

		protected:
			Graver();
		public:

			Graver(GraverType type, int graverGroup, int effectRadius, 
				Vec2Int defaultGraverEffectMag);
			~Graver();

			void ConfigureGraver(GraverType type, int graverGroup, int effectRadius, 
				Vec2Int defaultGraverEffectMag);

			void GraverUpdate();
			void DestroySelf();

		};
	}
}