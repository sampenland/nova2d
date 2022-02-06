#pragma once
#include "../logging/logging.h"
#include <map>
#include <string>

namespace novazero
{
	namespace core
	{
		class Meta
		{

		private:
		protected:
			Meta() {};
		public:

			std::map<std::string, std::string> s_Meta;
			void MetaAdd(std::string key, std::string value)
			{
				s_Meta[key] = value;
			}

			std::string MetaGet(std::string key) 
			{ 
				if (s_Meta.find(key) == s_Meta.end())
				{
					LOG(LVL_WARNING, "No meta with key: " + key);
					return "\0";
				}
				return s_Meta[key];
			}

		};
	}
}