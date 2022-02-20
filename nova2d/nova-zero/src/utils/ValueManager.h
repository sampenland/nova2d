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
			static float* AddValue(const std::string& valueName, float value);
			static float GetValue(const std::string& valueName);
			static float* GetRefToValue(const std::string& valueName);

		};
	}
}