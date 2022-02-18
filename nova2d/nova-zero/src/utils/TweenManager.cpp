#pragma once
#include "TweenManager.h"
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		using namespace core;

		TweenManager::TweenManager() { }

		void TweenManager::SetTweenType(Tween& t, TweenTypes type)
		{
			t.tweenEasingFunc = &Tweens::EaseOutCubic;

			switch (type)
			{

			case TweenTypes::EaseInSine:
				t.tweenEasingFunc = &Tweens::EaseInSine;
				break;
			case TweenTypes::EaseOutSine:
				t.tweenEasingFunc = &Tweens::EaseOutSine;
				break;
			case TweenTypes::EaseInOutSine:
				t.tweenEasingFunc = &Tweens::EaseInOutSine;
				break;

			case TweenTypes::EaseInQuad:
				t.tweenEasingFunc = &Tweens::EaseInQuad;
				break;
			case TweenTypes::EaseOutQuad:
				t.tweenEasingFunc = &Tweens::EaseOutQuad;
				break;
			case TweenTypes::EaseInOutQuad:
				t.tweenEasingFunc = &Tweens::EaseInOutQuad;
				break;

			case TweenTypes::EaseInCubic:
				t.tweenEasingFunc = &Tweens::EaseInCubic;
				break;
			case TweenTypes::EaseOutCubic:
				t.tweenEasingFunc = &Tweens::EaseOutCubic;
				break;
			case TweenTypes::EaseInOutCubic:
				t.tweenEasingFunc = &Tweens::EaseInOutCubic;
				break;

			case TweenTypes::EaseInQuart:
				t.tweenEasingFunc = &Tweens::EaseInQuart;
				break;
			case TweenTypes::EaseOutQuart:
				t.tweenEasingFunc = &Tweens::EaseOutQuart;
				break;
			case TweenTypes::EaseInOutQuart:
				t.tweenEasingFunc = &Tweens::EaseInOutQuart;
				break;

			case TweenTypes::EaseInQuint:
				t.tweenEasingFunc = &Tweens::EaseInQuint;
				break;
			case TweenTypes::EaseOutQuint:
				t.tweenEasingFunc = &Tweens::EaseOutQuint;
				break;
			case TweenTypes::EaseInOutQuint:
				t.tweenEasingFunc = &Tweens::EaseInOutQuint;
				break;

			case TweenTypes::EaseInExpo:
				t.tweenEasingFunc = &Tweens::EaseInExpo;
				break;
			case TweenTypes::EaseOutExpo:
				t.tweenEasingFunc = &Tweens::EaseOutExpo;
				break;
			case TweenTypes::EaseInOutExpo:
				t.tweenEasingFunc = &Tweens::EaseInOutExpo;
				break;

			case TweenTypes::EaseInCirc:
				t.tweenEasingFunc = &Tweens::EaseInCirc;
				break;
			case TweenTypes::EaseOutCirc:
				t.tweenEasingFunc = &Tweens::EaseOutCirc;
				break;
			case TweenTypes::EaseInOutCirc:
				t.tweenEasingFunc = &Tweens::EaseInOutCirc;
				break;

			case TweenTypes::EaseInBack:
				t.tweenEasingFunc = &Tweens::EaseInBack;
				break;
			case TweenTypes::EaseOutBack:
				t.tweenEasingFunc = &Tweens::EaseOutBack;
				break;
			case TweenTypes::EaseInOutBack:
				t.tweenEasingFunc = &Tweens::EaseInOutBack;
				break;

			case TweenTypes::EaseInElastic:
				t.tweenEasingFunc = &Tweens::EaseInElastic;
				break;
			case TweenTypes::EaseOutElastic:
				t.tweenEasingFunc = &Tweens::EaseOutElastic;
				break;
			case TweenTypes::EaseInOutElastic:
				t.tweenEasingFunc = &Tweens::EaseInOutElastic;
				break;

			case TweenTypes::EaseInBounce:
				t.tweenEasingFunc = &Tweens::EaseInBounce;
				break;
			case TweenTypes::EaseOutBounce:
				t.tweenEasingFunc = &Tweens::EaseOutBounce;
				break;
			case TweenTypes::EaseInOutBounce:
				t.tweenEasingFunc = &Tweens::EaseInOutBounce;
				break;
			}
		}

		unsigned int TweenManager::AddTween(bool isFloat, void* propertyEffected, float start,
			float end, float durationMS, bool loop, bool autoDelete, TweenTypes type)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			SetTweenType(*t, type);
			
			t->durationMS = durationMS;
			t->invert = end < start;

			if (end < 0.f)
			{
				t->negate = true;
				end *= -1;
			}
			else
			{
				t->negate = false;
			}

			if (t->invert)
			{
				t->initStart = end;
				t->end = start;
			}
			else
			{
				t->initStart = start;			
				t->end = end;
			}

			t->current = t->initStart;
			t->xStart = 0.f;
			t->xCurrent = 0.f;

			if (t->negate)
			{
				t->xStep = ((t->initStart - t->end) / t->initStart) / (durationMS / 10);
			}
			else
			{
				t->xStep = ((t->end - t->initStart) / t->end) / (durationMS / 10);
			}

			if (isFloat)
			{
				t->isFloat = true;
				t->referenceF = (float*)propertyEffected;
			}
			else
			{
				t->isFloat = false;
				t->referenceI = (int*)propertyEffected;
			}

			t->loop = loop;
			t->deleteOnComplete = autoDelete;

			if (!autoDelete)
				LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(id));

			m_Tweens[id] = t;
			return id;
		}

		Tween& TweenManager::GetTween(unsigned int tweenID)
		{
			return *m_Tweens[tweenID];
		}

		void TweenManager::RemoveTween(unsigned int tweenID)
		{
			m_Tweens.erase(tweenID);
		}

		void TweenManager::SetTweenLoopValue(unsigned int tweenID, float valueBtw0And1)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				if (valueBtw0And1 < 0.f) valueBtw0And1 = 0.f;
				if (valueBtw0And1 > 1.f) valueBtw0And1 = 1.f;
				m_Tweens[tweenID]->loopResetValue = valueBtw0And1;
			}
		}

		void TweenManager::EnableTween(unsigned int tweenID, bool enabled, bool reset)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->enabled = enabled;

				if (reset)
					m_Tweens[tweenID]->xCurrent = 0;
			}
		}

		void TweenManager::SetTweenValue(unsigned int tweenID, float value)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				Tween& t = *m_Tweens[tweenID];

				if ((t.end > t.initStart ? t.end : t.initStart) < value) 
					value = (t.end > t.initStart ? t.end : t.initStart);
				t.xCurrent = value / (t.end > t.initStart ? t.end : t.initStart);
			}
		}

		void TweenManager::ResetDuration(unsigned int tweenID, float durationMS)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->durationMS = durationMS;

				if (m_Tweens[tweenID]->negate)
				{
					m_Tweens[tweenID]->xStep = ((m_Tweens[tweenID]->initStart - m_Tweens[tweenID]->end) / m_Tweens[tweenID]->initStart) / (durationMS / 10);
				}
				else
				{
					m_Tweens[tweenID]->xStep = ((m_Tweens[tweenID]->end - m_Tweens[tweenID]->initStart) / m_Tweens[tweenID]->end) / (durationMS / 10);
				}
			}
		}

		void TweenManager::ResetTween(unsigned int tweenID)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->xCurrent = 0;
			}
		}

		void TweenManager::Reconfigure(unsigned int tweenID, float start,
			float end, float durationMS, bool loop, bool autoDelete)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->completed = false;
				m_Tweens[tweenID]->durationMS = durationMS;
				m_Tweens[tweenID]->invert = end < start;

				if (end < 0.f)
				{
					m_Tweens[tweenID]->negate = true;
					end *= -1;
				}
				else if (start < 0.f)
				{
					m_Tweens[tweenID]->negate = true;
					start *= -1;
				}
				else
				{
					m_Tweens[tweenID]->negate = false;
				}

				if (m_Tweens[tweenID]->invert)
				{
					m_Tweens[tweenID]->initStart = end;
					m_Tweens[tweenID]->end = start;
				}
				else
				{
					m_Tweens[tweenID]->initStart = start;
					m_Tweens[tweenID]->end = end;
				}

				m_Tweens[tweenID]->current = m_Tweens[tweenID]->initStart;
				m_Tweens[tweenID]->xStart = 0.f;
				m_Tweens[tweenID]->xCurrent = 0.f;

				if (m_Tweens[tweenID]->negate)
				{
					m_Tweens[tweenID]->xStep = ((m_Tweens[tweenID]->initStart - m_Tweens[tweenID]->end) / m_Tweens[tweenID]->initStart) / (durationMS / 10);
				}
				else
				{
					m_Tweens[tweenID]->xStep = ((m_Tweens[tweenID]->end - m_Tweens[tweenID]->initStart) / m_Tweens[tweenID]->end) / (durationMS / 10);
				}
				
				m_Tweens[tweenID]->loop = loop;
				m_Tweens[tweenID]->deleteOnComplete = autoDelete;

				if (!autoDelete)
					LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(tweenID)); m_Tweens[tweenID]->loop = loop;
			}
		}

		void TweenManager::Update()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;
			for (it = m_Tweens.begin(); it != m_Tweens.end();)
			{
				if (it->second->completed)
				{
					if (it->second->deleteOnComplete)
					{
						it = m_Tweens.erase(it);
						continue;
					}
					else
					{
						it++;
						continue;
					}
				}

				if (!it->second->enabled)
				{
					it++;
					continue;
				}

				InterfaceToEasings(*it->second);

				it++;
			}
		};

		void TweenManager::InterfaceToEasings(Tween& tween)
		{
			// Increment x such that duration is full time of tween
			float percentToEnd = tween.tweenEasingFunc(tween.xCurrent);
			float value = percentToEnd * tween.end;
			
			if (tween.xCurrent < 1.0f)
			{
				tween.xCurrent += tween.xStep * n2dTimeScale;
			}
			else
			{
				if (tween.loop)
				{
					tween.xCurrent = tween.loopResetValue;
					return;
				}
				else
				{
					tween.completed = true;
					tween.xCurrent = 1.f;
					percentToEnd = 1.f;
				}
			}

			if (tween.negate)
			{
				if (!tween.invert)
				{
					value = (1.f - percentToEnd) * tween.initStart;
				}
				else
				{
					value = percentToEnd * tween.initStart;
				}
				value *= -1;
				value -= tween.end; // offset to starting value
			}
			else
			{
				if (tween.invert)
				{
					value = (1.f - percentToEnd) * tween.end;
				}
				value += tween.initStart;
			}

 			if (tween.isFloat)
			{
				*tween.referenceF = (float)value;
			}
			else
			{
				*tween.referenceI = (int)value;
			}
		}

		void TweenManager::ClearTweens()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;

			for (it = m_Tweens.begin(); it != m_Tweens.end(); )
			{
				it = m_Tweens.erase(it);
			}

			m_Tweens.clear();
		}
	}
}