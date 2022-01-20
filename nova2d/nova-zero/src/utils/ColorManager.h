#pragma once
#include "../graphics/Color.h"
#include <string>
#include <map>

namespace novazero
{
	namespace utils
	{
		using namespace graphics;

		class ColorManager
		{

		private:

			std::map<std::string, Color> m_ColorMap;

		public:

			ColorManager();
			~ColorManager();

			Color AddColor(const std::string name, Color color);
			Color AddColor(const std::string name, std::string hexCode, const Uint8 alpha);
			void RemoveColor(const std::string name);

			Color GetColor(const std::string name) const;

		};
	}
}