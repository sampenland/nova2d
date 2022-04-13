#include "DemoSceneContactListener.h"
#include "logging/logging.h"
#include "physics/PhySprite.h"

namespace testproject
{
	using namespace novazero::physics;

	DemoSceneContactListener::DemoSceneContactListener() {};

	void DemoSceneContactListener::BeginContact(b2Contact* contact)
	{
		PhySprite* contactA = (PhySprite*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		PhySprite* contactB = (PhySprite*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		
		if (contactA && contactB)
		{
			LOGS("Collision [ " + contactA->GetColliderName() + " ] & [ " + contactB->GetColliderName() + " ]");
		}
	}
	
	void DemoSceneContactListener::EndContact(b2Contact* contact)
	{
		PhySprite* contactA = (PhySprite*)(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		PhySprite* contactB = (PhySprite*)(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (contactA && contactB)
		{
			LOGS("Collision [ " + contactA->GetColliderName() + " ] & [ " + contactB->GetColliderName() + " ]");
		}
	}
}