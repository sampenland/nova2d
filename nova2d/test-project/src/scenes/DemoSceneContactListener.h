#pragma once
#include "physics/PhyContactListener.h"

namespace testproject
{
	using namespace novazero::physics;

	class DemoSceneContactListener :
		public PhyContactListener
	{

	public:

		DemoSceneContactListener();

		void BeginContact(b2Contact* contact) override;
		void EndContact(b2Contact* contact) override;

	};
}