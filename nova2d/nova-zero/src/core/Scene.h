#pragma once
#include "EventListener.h"
#include "../maths/Vec2.h"
#include <functional>
#include <vector>
#include <string>
#include "box2d/box2d.h"

namespace novazero
{
	namespace core
	{
		using namespace novazero::maths;

		class Scene : public EventListener
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

			bool m_Started = false;
			std::string m_SceneName = "";

			void EnablePhysics(bool enabled, Vec2 gravity);
			b2World* GetWorld() const;
			void PhysicsStep();

			virtual void Start() = 0;
			void Restart();
			void Clean();

			virtual void End() = 0;
			virtual void Update() = 0;

			void AddObjectToCleanUp(void* obj);
			void CleanUp();
		};
	}
}