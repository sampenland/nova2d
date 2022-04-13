#pragma once
#include "EventListener.h"
#include "../maths/Vec2.h"
#include <functional>
#include <vector>
#include <string>
#include "box2d/box2d.h"
#include "SDL.h"
#include "../core/Environment.h"
#include "../debug/PhysicsDebug.h"

namespace novazero
{
	namespace core
	{
		using namespace novazero::maths;
		using namespace novazero::debug;

		class Scene : 
			public EventListener
		{
		
		private:

			std::vector<void*> m_CleanUpObjects;
			
		private:

			// Physics
			float m_TimeStep = 1.f / 60.f;
			b2World* m_World = nullptr;
			bool m_PhysicsEnabled = false;
			b2Vec2* m_Gravity = nullptr;

		public:

			Scene(const std::string& sceneName);

			bool m_DebugDraw = false;
			bool m_Started = false;
			std::string m_SceneName = "";

			static Environment* s_Environment;

			void EnablePhysics(bool enabled, b2ContactListener* contactListener, Vec2 gravity = Vec2(0,0), float innerPadding = 0.f);
			b2World* GetWorld() const;
			
			void PhysicsStep();
			void PhysicsEnableDebug(bool isDebug);

			void EnableLights(Uint8 worldLightIntensity);

			virtual void Start() = 0;
			void Restart();
			void Clean();

			virtual void End() = 0;
			virtual void Update() = 0;

			void AddObjectToCleanUp(void* obj);
			void CleanUp();

		public:

			static PhysicsDebug* s_PhysicsDrawer;
		};
	}
}