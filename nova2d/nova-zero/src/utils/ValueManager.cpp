#include "ValueManager.h"

namespace novazero
{
	namespace utils
	{
		std::map<std::string, float> ValueManager::s_Values;

		float* ValueManager::AddValue(const std::string& valueName, float value)
		{
			if (s_Values.find(valueName) != s_Values.end())
			{
				LOG(LVL_W, valueName + " ALREADY in values...overwriting.");
				s_Values[valueName] = value;
			}

			s_Values[valueName] = value;

			return &s_Values[valueName];
		}

		float ValueManager::GetValue(const std::string& valueName)
		{
			if (s_Values.find(valueName) != s_Values.end())
			{
				return s_Values[valueName];
			}
			else
			{
				LOG(LVL_W, valueName + " NOT FOUND...returning 0.0f");
				return 0.f;
			}
		}

		float* ValueManager::GetRefToValue(const std::string& valueName)
		{
			if (s_Values.find(valueName) != s_Values.end())
			{
				return &s_Values[valueName];
			}
			else
			{
				LOG(LVL_W, valueName + " NOT FOUND...returning 0.0f");
				return nullptr;
			}
		}
	}
}