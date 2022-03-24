#include "ColorManager.h"

#include "../logging/logging.h"
#include <regex>

namespace novazero
{
	namespace utils
	{
		using namespace logging;

		ColorManager::ColorManager() {}

		Color* ColorManager::AddColor(const std::string& name, Color* c)
		{
			m_ColorMap.insert(std::pair<std::string, Color*>(name, c));
			return GetColor(name);
		}

		Color* ColorManager::AddColor(const std::string& name, std::string& hexCode, const Uint8 alpha)
		{
			std::regex pattern("([0-9a-fA-F]{6})");
			std::smatch match;
			if (std::regex_match(hexCode, match, pattern))
			{
				int r, g, b;
				int s = sscanf(match.str(1).c_str(), "%2x%2x%2x", &r, &g, &b);

				Color* c = new Color(r, g, b, alpha);
				return AddColor(name, c);
			}

			return new Color(0, 0, 0, 255);
		}

		Color* ColorManager::AddColor(const std::string& name, const char* hexCode, const Uint8 alpha)
		{
			std::string hc = hexCode;
			std::regex pattern("([0-9a-fA-F]{6})");
			std::smatch match;
			if (std::regex_match(hc, match, pattern))
			{
				int r, g, b;
				int s = sscanf(match.str(1).c_str(), "%2x%2x%2x", &r, &g, &b);

				Color* c = new Color(r, g, b, alpha);
				return AddColor(name, c);
			}

			return new Color(0, 0, 0, 255);
		}

		void ColorManager::RemoveColor(const std::string& name)
		{
			m_ColorMap.erase(name);
		}

		Color* ColorManager::GetColor(const std::string& name) const
		{
			try {
				return m_ColorMap.at(name);
			}
			catch (const std::out_of_range& oor) 
			{
				LOG(LVL_NON_FATAL_ERROR, "Couldn't find color: " + name + ". Returned BLACK color.");
				LOG(LVL_NON_FATAL_ERROR, oor.what());
				return new Color(0, 0, 0, 1);
			}
			
		}

		void ColorManager::DestroySelf()
		{
			m_ColorMap.clear();
		}
	}
}