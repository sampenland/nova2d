#pragma once
#include "TweenManager.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maths
	{
		using namespace core;

		TweenManager::TweenManager()
		{
			m_CleanID = n2dAddUpdater(TweenManager::Update, this);
		}

		void TweenManager::AddTween(void* propertyEffected, float start, float end, float durationMS)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			t->propertyEffected = propertyEffected;
			t->step = (end - start) / durationMS;
			t->durationLeft = durationMS;

			m_Timers[id] = t;
		}

		void TweenManager::Update()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;
			for (it = m_Timers.begin(); it != m_Timers.end(); it++)
			{
				it->second->durationLeft = (float)it->second->durationLeft - it->second->step;
				
				if (it->second->start + it->second->start < it->second->end)
				{
					*(it->second->propertyEffected) += 1;
				}

				if (it->second->durationLeft < 0)
				{
					removeIDs.push_back(it->first);
				}
			}

			for (size_t i = 0; i < removeIDs.size(); i++)
			{
				m_Timers.erase(removeIDs[i]);
			}
		};

		void TweenManager::DestroySelf()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;

			for (it = m_Timers.begin(); it != m_Timers.end(); it++)
			{
				removeIDs.push_back(it->first);
			}

			for (size_t i = 0; i < removeIDs.size(); i++)
			{
				m_Timers.erase(removeIDs[i]);
			}

			n2dRemoveUpdater(m_CleanID);
		}
	}
}