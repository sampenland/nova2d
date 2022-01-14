#pragma once
#include <vector>
#include "SDL.h"
#include <functional>

typedef std::function<bool(SDL_Keycode)> f_KeyConditionalFunction;
typedef std::function<void()> f_EventPtrFunction;

namespace novazero
{
	namespace core
	{
		class EventListener
		{

		private:
			
			std::vector<f_KeyConditionalFunction> m_KeysConditions;
			std::vector<f_EventPtrFunction> m_KeysEvents;
			std::vector<SDL_Keycode> m_KeyCodes;

			unsigned int m_ID = 0;

		public:
			
			EventListener();
			~EventListener();

			void EventStep();

			void AddKeysEventListener(SDL_KeyCode key, f_KeyConditionalFunction conditionalFunction, f_EventPtrFunction executeFunction);
			void RemoveEventListener(SDL_KeyCode key);

			bool operator==(const EventListener& other);

		};
	}
}