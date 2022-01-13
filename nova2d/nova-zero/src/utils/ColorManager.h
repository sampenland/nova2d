#pragma once
#include "../graphics/Color.h"
#include "../logging/logging.h"
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

			void AddColor(const std::string name, Color color);
			void RemoveColor(const std::string name);

			Color GetColor(const std::string name) const;

		};
	}
}