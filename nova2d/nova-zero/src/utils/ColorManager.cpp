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

		void ColorManager::AddColor(const std::string name, Color c)
		{
			m_ColorMap.insert(std::pair<std::string, Color>(name, c));
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
				return Color(0, 0, 0, 1);
			}
			
		}
	}
}