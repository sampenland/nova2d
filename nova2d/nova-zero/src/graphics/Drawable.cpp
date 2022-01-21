#include "Drawable.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{

		Drawable::Drawable()
			: m_Layer(0)
		{
			m_ID = n2dGameGetID();
		};

		Drawable::~Drawable()
		{

		}

	}
}