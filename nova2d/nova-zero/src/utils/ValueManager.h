#pragma once
#include <map>
#include <string>
#include "../logging/logging.h"

namespace novazero
{
	namespace utils
	{
		class ValueManager
		{

		private:

			ValueManager() {};

		public:
						
			static std::map<std::string, float> s_Values;
			static std::map<std::string, float> s_PersistentValues;
			static float* AddValue(const std::string& valueName, float value, bool persistent = false);
			static void RemoveValue(const std::string& valueName, bool persistent = false);
			static float GetValue(const std::string& valueName, bool persistent = false);
			static float* GetRefToValue(const std::string& valueName, bool persistent = false);

			static void ClearValues(bool persistent = false);

		};
	}
}