#pragma once
#include "../core/Deleteable.h"
#include "../maths/Vec2Int.h"
#include "../core/BoundUser.h"
#include "../graphics/Sprite.h"
#include "../core/Positional.h"

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
			YPushX,
			XPushY,
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
		
			Vec2Int m_GraverEffectMagnitude;
			Vec2Int m_GraverInfluencedMag;
			GraverType m_GraverType = GraverType::Vec2Force;
			Positional* m_Physical = nullptr;
			std::vector<Graver*> m_EffectedGravers;

		protected:
			Graver();
		public:

			Graver(GraverType type, int effectRadius, 
				Vec2Int defaultGraverEffectMag, Positional* physicalHook);
			~Graver();

			void ConfigureGraver(GraverType type, int effectRadius, 
				Vec2Int defaultGraverEffectMag, Positional* physicalHook);

			void AddEffectedGraver(Graver* graver);
			void RemoveEffectedGraver(Graver* graver);

			void GraverUpdate();
			void DestroySelf();

			bool GraverWithinEffect(const Graver& graver);

		};
	}
}