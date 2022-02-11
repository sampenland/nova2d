#pragma once
#include "TweenManager.h"
#include "../core/Game.h"

namespace novazero
{
	namespace maths
	{
		using namespace core;

		struct Tween
		{
			std::function<float(float)> tweenEasingFunc = nullptr;

			float xStart = 0.f;
			float xStep = 0.f;
			float xCurrent = 0.0f;
			const float xEnd = 1.f;

			float durationMS = 1000.f;
			float initStart = 0.f;
			float end = 0.f;
			float current = 0.f;
			bool invert = false;
			float* referenceP;
			bool loop = false;
			bool deleteOnComplete = true;
			bool enabled = true;
		};

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

		unsigned int TweenManager::AddTween(float* propertyEffected, float start,
			float end, float durationMS, bool loop, bool autoDelete, TweenTypes type)
		{
			unsigned int id = n2dGameGetID();

			Tween* t = new Tween();

			SetTweenType(*t, type);
			
			t->durationMS = durationMS;
			t->invert = end < start;

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
			t->xStep = ((t->end - t->initStart) / t->end) / (durationMS/10); // how much x to increment per millisecond

			t->referenceP = propertyEffected;
			t->loop = loop;
			t->deleteOnComplete = autoDelete;

			if (!autoDelete)
				LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(id));

			m_Tweens[id] = t;
			return id;
		}

		void TweenManager::RemoveTween(unsigned int tweenID)
		{
			m_Tweens.erase(tweenID);
		}

		void TweenManager::EnableTween(unsigned int tweenID, bool enabled, bool reset)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->enabled = enabled;

				if (reset)
					m_Tweens[tweenID]->current = m_Tweens[tweenID]->initStart;
			}
		}

		void TweenManager::ResetTween(unsigned int tweenID)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				m_Tweens[tweenID]->current = m_Tweens[tweenID]->initStart;
			}
		}

		void TweenManager::Reconfigure(unsigned int tweenID, float start,
			float end, float durationMS, bool loop, bool autoDelete)
		{
			if (m_Tweens.find(tweenID) != m_Tweens.end())
			{
				
				// TODO: re setup values

				m_Tweens[tweenID]->loop = loop;
				m_Tweens[tweenID]->deleteOnComplete = autoDelete;

				if (!autoDelete)
					LOG(LVL_WARNING, "Orphan Tween: " + std::to_string(tweenID));

			}
		}

		void TweenManager::Update()
		{
			std::vector<unsigned int> removeIDs;
			std::map<unsigned int, Tween*>::iterator it;
			for (it = m_Tweens.begin(); it != m_Tweens.end();)
			{
				if (it->second->xCurrent >= 1.f)
				{
					it = m_Tweens.erase(it);
					continue;
				}

				if (!it->second->enabled)
					continue;

				InterfaceToEasings(*it->second);

				it++;
			}
		};

		void TweenManager::InterfaceToEasings(Tween& tween)
		{
			// Increment x such that duration is full time of tween
			float percentToEnd = tween.tweenEasingFunc(tween.xCurrent);
			float value = percentToEnd * tween.end;
			
			tween.xCurrent += tween.xStep;

			if (tween.invert)
			{
				value = (1.f - percentToEnd) * tween.end;
			}
			LOG(LVL_CONFIRMATION, std::to_string(value));

			float current = tween.current / tween.end;
			float easingValue = tween.tweenEasingFunc(current);

			*tween.referenceP = value;

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