#include "ColorManager.h"

namespace novazero
{
	namespace utils
	{
		using namespace logging;

		ColorManager::ColorManager()
		{
			
		}

		ColorManager::~ColorManager()
		{

		}

		Color ColorManager::AddColor(const std::string name, Color c)
		{
			m_ColorMap.insert(std::pair<std::string, Color>(name, c));
			return GetColor(name);
		}

		Color ColorManager::AddColor(const std::string name, std::string hexCode, const Uint8 alpha)
		{
			std::regex pattern("([0-9a-fA-F]{6})");
			std::smatch match;
			if (std::regex_match(hexCode, match, pattern))
			{
				int r, g, b;
				int s = sscanf(match.str(1).c_str(), "%2x%2x%2x", &r, &g, &b);

				Color c(r, g, b, alpha);
				return AddColor(name, c);
			}

			return Color(0, 0, 0, 255);
		}

		void ColorManager::RemoveColor(const std::string name)
		{
			m_ColorMap.erase(name);
		}

		Color ColorManager::GetColor(const std::string name) const
		{
			try {
				return m_ColorMap.at(name);
			}
			catch (const std::out_of_range& oor) {
				LOG(name);
				LOG("Couldn't find color.");
				const char* ex = oor.what();
				LOG(ex);
				return Color(0, 0, 0, 1);
			}
			
		}
	}
}