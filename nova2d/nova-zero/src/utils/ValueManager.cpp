#include "ValueManager.h"

namespace novazero
{
	namespace utils
	{
		std::map<std::string, float> ValueManager::s_Values;
		std::map<std::string, float> ValueManager::s_PersistentValues;

		void ValueManager::RemoveValue(const std::string& valueName, bool persistent)
		{
			if (persistent)
			{
				if (s_PersistentValues.find(valueName) != s_PersistentValues.end())
				{
					s_PersistentValues.erase(valueName);
				}
			}
			else
			{
				if (s_Values.find(valueName) != s_Values.end())
				{
					s_Values.erase(valueName);
				}
			}
		}

		void ValueManager::ClearValues(bool persistent)
		{
			if (persistent)
			{
				s_PersistentValues.clear();
				s_Values.clear();
			}
			else
			{
				s_Values.clear();
			}
		}

		float* ValueManager::AddValue(const std::string& valueName, float value, bool persistent)
		{
			if (persistent)
			{
				if (s_PersistentValues.find(valueName) != s_PersistentValues.end())
				{
					LOG(LVL_W, valueName + " ALREADY in Persistent Values... WILL NOT OVERWRITE.", __FILE__, __LINE__);
					return nullptr;
				}

				s_PersistentValues[valueName] = value;
				return &s_PersistentValues[valueName];
			}
			else
			{
				if (s_Values.find(valueName) != s_Values.end())
				{
					LOG(LVL_W, valueName + " ALREADY in Values...overwriting.", __FILE__, __LINE__);
					s_Values[valueName] = value;
				}

				s_Values[valueName] = value;

				return &s_Values[valueName];
			}
		}

		float ValueManager::GetValue(const std::string& valueName, bool persistent)
		{
			if (persistent)
			{
				if (s_PersistentValues.find(valueName) != s_PersistentValues.end())
				{
					return s_PersistentValues[valueName];
				}
				else
				{
					LOG(LVL_W, valueName + " NOT FOUND in Persistent Values...returning 0.0f", __FILE__, __LINE__);
					return 0.f;
				}
			}
			else
			{
				if (s_Values.find(valueName) != s_Values.end())
				{
					return s_Values[valueName];
				}
				else
				{
					LOG(LVL_W, valueName + " NOT FOUND in Values...returning 0.0f", __FILE__, __LINE__);
					return 0.f;
				}
			}
		}

		float* ValueManager::GetRefToValue(const std::string& valueName, bool persistent)
		{
			if (persistent)
			{
				if (s_PersistentValues.find(valueName) != s_PersistentValues.end())
				{
					return &s_PersistentValues[valueName];
				}
				else
				{
					LOG(LVL_W, valueName + " NOT FOUND in Persistent Values...returning 0.0f", __FILE__, __LINE__);
					return nullptr;
				}
			}
			else
			{
				if (s_Values.find(valueName) != s_Values.end())
				{
					return &s_Values[valueName];
				}
				else
				{
					LOG(LVL_W, valueName + " NOT FOUND in Values...returning 0.0f", __FILE__, __LINE__);
					return nullptr;
				}
			}
		}
	}
}