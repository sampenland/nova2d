#include "DemoSceneContactListener.h"
#include "logging/logging.h"
#include "physics/PhySprite.h"
#include "physics/PhyBase.h"

namespace testproject
{
	using namespace novazero::physics;

	DemoSceneContactListener::DemoSceneContactListener() {};

	void DemoSceneContactListener::BeginContact(b2Contact* contact)
	{
		PhyBase* contactA = reinterpret_cast<PhyBase*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		PhyBase* contactB = reinterpret_cast<PhyBase*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		
		if (contactA && contactB)
		{
			LOGS("Collision [ " + contactA->GetColliderName() + " ] & [ " + contactB->GetColliderName() + " ]");
		}
	}
	
	void DemoSceneContactListener::EndContact(b2Contact* contact)
	{
		PhyBase* contactA = reinterpret_cast<PhyBase*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		PhyBase* contactB = reinterpret_cast<PhyBase*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (contactA && contactB)
		{
			LOGS("Collision [ " + contactA->GetColliderName() + " ] & [ " + contactB->GetColliderName() + " ]");
		}
	}
}