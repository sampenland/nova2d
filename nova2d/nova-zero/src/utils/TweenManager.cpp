#pragma once
#include "TweenManager.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maths
	{
		using namespace core;

		TweenManager::TweenManager() { }

		void TweenManager::SetTweenType(Tween& t, TweenTypes type)
		{
			t.tweenEasingFunc = &Tweens::EaseOutCubic;

			switch (type)
			{
				case TweenTypes::
			}
		}

		unsigned int TweenManager::AddTweenInt(TweenTypes type, int* propertyEffected, float start, 
			float end, float durationMS, bool loop, bool autoDelete)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			

			t->initStart = start;
			t->isFloat = false;
			t->intPropertyEffected = propertyEffected;
			t->step = (end - start) / (durationMS / 10);
			t->durationLeft = durationMS;
			t->current = start;
			t->end = end;
			t->loop = loop;
			t->deleteOnComplete = autoDelete;

			if (!autoDelete)
				LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(id));

			m_Timers[id] = t;
			return id;
		}

		unsigned int TweenManager::AddTweenFloat(TweenTypes type, float* propertyEffected, float start, 
			float end, float durationMS, bool loop, bool autoDelete)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			t->type = type;
			t->initStart = start;
			t->isFloat = true;
			t->floatPropertyEffected = propertyEffected;
			t->step = (end - start) / (durationMS / 10);
			t->durationLeft = durationMS;
			t->current = start;
			t->end = end;
			t->loop = loop;
			t->deleteOnComplete = autoDelete;
			
			if (!autoDelete)
				LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(id));

			m_Timers[id] = t;
			return id;
		}

		void TweenManager::RemoveTween(unsigned int tweenID)
		{
			m_Timers.erase(tweenID);
		}

		void TweenManager::EnableTween(unsigned int tweenID, bool enabled, bool reset)
		{
			if (m_Timers.find(tweenID) != m_Timers.end())
			{
				m_Timers[tweenID]->enabled = enabled;
				
				if(reset)
					m_Timers[tweenID]->current = m_Timers[tweenID]->initStart;
			}
		}

		void TweenManager::ResetTween(unsigned int tweenID)
		{
			if (m_Timers.find(tweenID) != m_Timers.end())
			{
				m_Timers[tweenID]->current = m_Timers[tweenID]->initStart;
			}
		}

		void TweenManager::Reconfigure(unsigned int tweenID, float start, 
			float end, float durationMS, bool loop, bool autoDelete)
		{
			if (m_Timers.find(tweenID) != m_Timers.end())
			{
				m_Timers[tweenID]->current = start;
				m_Timers[tweenID]->initStart = start;
				m_Timers[tweenID]->step = (end - start) / (durationMS / 10);;
				m_Timers[tweenID]->end = end;
				m_Timers[tweenID]->durationLeft = durationMS;
				m_Timers[tweenID]->loop = loop;
				m_Timers[tweenID]->deleteOnComplete = autoDelete;

				if (!autoDelete)
					LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(tweenID));

			}
		}

		void TweenManager::Update()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;
			for (it = m_Timers.begin(); it != m_Timers.end(); it++)
			{
				if (!it->second->enabled)
					continue;

				if (it->second->isFloat)
				{
					FloatTween(it);
					
					if (((it->second->step < 0) && (*it->second->floatPropertyEffected < it->second->end)) ||
						it->second->step > 0 && (*it->second->floatPropertyEffected > it->second->end))
					{
						if (it->second->loop)
						{
							it->second->current = it->second->initStart;
						}
						else
						{
							if (it->second->deleteOnComplete)
								removeIDs.push_back(it->first);
							else
								it->second->enabled = false;
						}
					}
				
				}
				else
				{
					IntTween(it);

					if (((it->second->step < 0) && (*it->second->intPropertyEffected < it->second->end)) ||
						it->second->step > 0 && (*it->second->intPropertyEffected > it->second->end))
					{
						if (it->second->loop)
						{
							it->second->current = it->second->initStart;
						}
						else
						{
							if(it->second->deleteOnComplete)
								removeIDs.push_back(it->first);
							else
								it->second->enabled = false;
						}
					}

				}	
			}

			for (size_t i = 0; i < removeIDs.size(); i++)
			{
				m_Timers.erase(removeIDs[i]);
			}
		};

		void TweenManager::FloatTween(std::map<unsigned int, Tween*>::iterator it)
		{
			it->second->current += it->second->step;
			*it->second->floatPropertyEffected = it->second->current;
		}

		void TweenManager::IntTween(std::map<unsigned int, Tween*>::iterator it)
		{
			it->second->current += it->second->step;
			*it->second->intPropertyEffected = it->second->current;
		}

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