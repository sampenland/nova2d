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
			
			if (isFloat)
			{
				t->referenceF = (float*)propertyEffected;
			}
			else
			{
				t->referenceI = (int*)propertyEffected;
			}

			m_Tweens[id] = t;

			Reconfigure(id, start, end, durationMS, loop, autoDelete);

			return id;
		}

		void TweenManager::Reconfigure(unsigned int tweenID, float start,
			float end, float durationMS, bool loop, bool autoDelete)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				Tween& tween = *m_Tweens[tweenID];

				tween.completed = false;
				tween.durationMS = durationMS;
				tween.invert = end < start;

				if (start < 0.f && end < 0.f)
				{
					if (start < end)
					{
						CreateTweenNegToNegInc(tween, start, end, durationMS);
					}
					else
					{
						CreateTweenNegToNegDec(tween, start, end, durationMS);
					}
				}
				else if (start < 0.f && end != 0.f)
				{
					CreateTweenNegToPos(tween, start, end, durationMS);
				}
				else if (start < 0.f && end == 0.f)
				{
					CreateTweenNegToZero(tween, start, end, durationMS);

				}
				else if (start > 0.f && end > 0.f)
				{
					if (start > end)
					{
						CreateTweenPosToPosDec(tween, start, end, durationMS);
					}
					else
					{
						CreateTweenPosToPosInc(tween, start, end, durationMS);
					}
				}
				else if (end < 0.f && start == 0.f)
				{
					CreateTweenZeroToNeg(tween, start, end, durationMS);
				}
				else if(end == 0.f && start > 0.f)
				{
					CreateTweenPosToZero(tween, start, end, durationMS);
				}
				else if (start == 0 && end > 0.f)
				{
					CreateTweenZeroToPos(tween, start, end, durationMS);
				}
				else if (start > 0.f && end < 0.f)
				{
					CreateTweenPosToNeg(tween, start, end, durationMS);
				}

				tween.current = tween.initStart;
				tween.xStart = 0.f;
				tween.xCurrent = 0.f;

				tween.loop = loop;
				tween.deleteOnComplete = autoDelete;

				if (tween.xStep == 0.0f)
				{
					tween.completed = true;
				}

				if (!autoDelete && n2dDebugVerbose)
					LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(tweenID)); tween.loop = loop;
			}
		}

		// ----------------------------------------------------------------------

		void TweenManager::CreateTweenNegToNegDec(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = true;

			tween.offset = -start;

			tween.initStart = -start;
			tween.end = end - start;
			tween.xStep = (std::abs(end - start) / (durationMS));
		}

		void TweenManager::CreateTweenNegToNegInc(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = true;

			tween.offset = -end;

			tween.initStart = start;
			tween.end = end;
			tween.xStep = std::abs(end - start) / (durationMS);
		}

		void TweenManager::CreateTweenNegToPos(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = false;
			tween.invert = false;

			tween.offset = start;

			tween.initStart = start;
			tween.end = end;
			tween.xStep = std::abs(end - start) / (durationMS);
		}

		void TweenManager::CreateTweenPosToNeg(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = false;
			tween.invert = true;

			tween.offset = end;

			tween.initStart = end;
			tween.end = start;
			tween.xStep = std::abs(end - start) / (durationMS);
		}

		void TweenManager::CreateTweenPosToPosDec(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = false;
			tween.invert = true;

			tween.offset = end;

			tween.initStart = start - end;
			tween.end = end;
			tween.xStep = std::abs(end - start) / (durationMS);
		}

		void TweenManager::CreateTweenPosToPosInc(Tween& tween, float start, float end, float durationMS)
		{
			tween.negate = false;
			tween.invert = false;

			tween.offset = start;

			tween.initStart = start;
			tween.end = end;
			tween.xStep = std::abs(end - start) / (durationMS);
		}

		void TweenManager::CreateTweenZeroToPos(Tween& tween, float start, float end, float durationMS)
		{
			tween.offset = 0;
			tween.negate = false;

			tween.initStart = start;
			tween.end = end;

			tween.xStep = end / (durationMS);
		}

		void TweenManager::CreateTweenZeroToNeg(Tween& tween, float start, float end, float durationMS)
		{
			tween.offset = 0;
			tween.negate = true;

			tween.initStart = end + -start;
			tween.end = 0;

			tween.xStep = std::abs(end) / (durationMS);
		}

		void TweenManager::CreateTweenNegToZero(Tween& tween, float start, float end, float durationMS)
		{
			tween.offset = 0;
			tween.negate = false;
			tween.invert = true;

			tween.initStart = start;
			tween.end = end;

			tween.xStep = -start / (durationMS);
		}

		void TweenManager::CreateTweenPosToZero(Tween& tween, float start, float end, float durationMS)
		{
			tween.offset = 0;
			tween.negate = false;
			tween.invert = true;

			tween.initStart = start;
			tween.end = end;

			tween.xStep = start / (durationMS);
		}

		// ----------------------------------------------------------------------

		Tween& TweenManager::GetTween(unsigned int tweenID)
		{
			return *m_Tweens[tweenID];
		}

		void TweenManager::RemoveTween(unsigned int tweenID)
		{
			m_Tweens.erase(tweenID);
		}

		void TweenManager::RemoveOffset(unsigned int tweenID)
		{
			m_Tweens[tweenID]->offset = 0.f;
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
				tween.xCurrent += tween.xStep * n2dTimeScale * (n2dDeltaTime / 250);
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
				
					if (tween.isFloat)
					{
						*tween.referenceF = (float)tween.end;
					}
					else
					{
						*tween.referenceI = (int)tween.end;
					}
				}
			}
			
			if (tween.negate)
			{
				if (!tween.invert)
				{
					value = (1.f - percentToEnd) * (tween.initStart - tween.end);
				}
				else
				{
					if (tween.end < tween.initStart && tween.end == 0)
					{
						value = percentToEnd * tween.initStart;
					}
					else if (tween.end < tween.initStart)
					{
						value = percentToEnd * tween.end;
					}
					else
					{
						value = percentToEnd * tween.initStart;
					}
				}
				value -= tween.offset;
			}
			else
			{
				if (tween.invert && tween.end == 0)
				{
					value = (1.f - percentToEnd) * tween.initStart;
				}
				else if (tween.invert)
				{
					if (tween.initStart < tween.end)
					{
						value = (1.f - percentToEnd) * (tween.end - tween.initStart);
					}
					else
					{
						value = (1.f - percentToEnd) * tween.initStart;
					}
				}
				else if (tween.end > tween.initStart)
				{
					value = percentToEnd * (tween.end - tween.initStart);
				}
				else
				{
					value = percentToEnd * tween.initStart;
				}
				value += tween.offset;
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