#pragma once
#include "../core/Deleteable.h"
#include "../maths/Vec2Int.h"
#include "../core/BoundUser.h"
#include "../graphics/Sprite.h"
#include "../core/Positional.h"
#include "../debug/DrawCircle.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;
		using namespace debug;

		enum class GraverType
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
			float m_GraverEffectRadius = 2.f;
			bool m_LookAtTarget = true;
		
			Vec2 m_GraverEffectMagnitude;
			Vec2 m_GraverInfluencedMag;
			GraverType m_GraverType = GraverType::Vec2Force;
			Positional* m_Physical = nullptr;
			std::vector<Graver*> m_EffectedGravers;
			DrawCircle* m_EffectCircle = nullptr;

		protected:
			Graver();
		public:

			Graver(GraverType type, float effectRadius,
				Vec2 defaultGraverEffectMag, Positional* physicalHook);

			void ConfigureGraver(GraverType type, float effectRadius, 
				Vec2 defaultGraverEffectMag, Positional* physicalHook);

			void GonfigureLookAt(bool lookAt) { m_LookAtTarget = lookAt; }

			void ConfigureGraverVisible(bool filled, std::string fillColor, std::string outlineColor,
				int radius, char layer);

			void AddEffectedGraver(Graver* graver);
			void RemoveEffectedGraver(Graver* graver);

			void GraverUpdate();
			void DestroySelf();

			bool GraverWithinEffect(const Graver& graver);

		};
	}
}