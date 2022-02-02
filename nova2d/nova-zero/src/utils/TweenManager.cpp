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
			
		}

		unsigned int TweenManager::AddTweenInt(int* propertyEffected, float start, float end, float durationMS, bool loop)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			t->initStart = start;
			t->isFloat = false;
			t->intPropertyEffected = propertyEffected;
			t->step = (end - start) / (durationMS / 10);
			t->durationLeft = durationMS;
			t->start = start;
			t->end = end;
			t->loop = loop;

			m_Timers[id] = t;
			return id;
		}

		unsigned int TweenManager::AddTweenFloat(float* propertyEffected, float start, float end, float durationMS, bool loop)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			t->initStart = start;
			t->isFloat = true;
			t->floatPropertyEffected = propertyEffected;
			t->step = (end - start) / (durationMS / 10);
			t->durationLeft = durationMS;
			t->start = start;
			t->end = end;
			t->loop = loop;

			m_Timers[id] = t;
			return id;
		}

		void TweenManager::RemoveTween(unsigned int tweenID)
		{
			m_Timers.erase(tweenID);
		}

		void TweenManager::Update()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;
			for (it = m_Timers.begin(); it != m_Timers.end(); it++)
			{
				if (it->second->isFloat)
				{
					it->second->start += it->second->step;
					*it->second->floatPropertyEffected = it->second->start;
				}
				else
				{
					it->second->start += it->second->step;
					*it->second->intPropertyEffected = (int)it->second->start;
				}

				if (((it->second->step < 0) && (*it->second->intPropertyEffected < it->second->end)) || 
					it->second->step > 0 && (*it->second->intPropertyEffected > it->second->end))
				{
					if (it->second->loop)
					{
						it->second->start = it->second->initStart;
					}
					else
					{
						removeIDs.push_back(it->first);
					}
				}	

				//TODO: float tween
			}

			for (size_t i = 0; i < removeIDs.size(); i++)
			{
				m_Timers.erase(removeIDs[i]);
			}
		};

		void TweenManager::ClearTweens()
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

			m_Timers.clear();
		}
	}
}