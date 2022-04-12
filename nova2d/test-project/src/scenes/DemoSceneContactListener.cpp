#include "DemoSceneContactListener.h"
#include "logging/logging.h"

namespace testproject
{
	using namespace novazero::physics;

	DemoSceneContactListener::DemoSceneContactListener() {};

	void DemoSceneContactListener::BeginContact(b2Contact* contact)
	{
		LOGS("B");
	}
	
	void DemoSceneContactListener::EndContact(b2Contact* contact)
	{
		LOGS("E");
	}
}