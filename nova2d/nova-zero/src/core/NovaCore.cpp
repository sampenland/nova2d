#include "NovaCore.h"
#include "Game.h"
#include "../utils/ValueManager.h"

namespace novazero
{
	unsigned int n2dGameGetID()
	{
		return Game::GetNextID();
	}

	void n2dDebugSet(bool isDebug)
	{
		Game::SetDebug(isDebug);
	}

	void n2dDebugVerboseSet(bool isDebug)
	{
		Game::SetDebugVerbose(isDebug);
	}

	void n2dZoomCamera(float zoomLevel)
	{
		Game::GetCamera()->SetZoom(zoomLevel);
	}

	void n2dEnableCameraFreeMove(bool enabled)
	{
		Game::GetCamera()->EnableFreeWASDMove(enabled);
	}

	void n2dPauseGame(bool pause)
	{
		Game::PauseGame(pause);
	}

	void n2dPauseKeySet(SDL_KeyCode key)
	{
		Game::s_PauseKey = key;
	}
		
	void n2dPauseKeyClear()
	{
		Game::s_PauseKey = SDLK_WWW;
	}

	void n2dTimeScaleSet(float timeScale)
	{
		Game::s_TimeScale = timeScale;
	}

	float* n2dValueManagerAdd(std::string name, float value, bool persist)
	{
		return ValueManager::AddValue(name, value, persist);
	}

	float n2dValueManagerGet(std::string name)
	{
		return ValueManager::GetValue(name);
	}

	float* n2dValueManagerGetRef(std::string name)
	{
		return ValueManager::GetRefToValue(name);
	}

	void n2dAddTimeline(std::string timelineName, TimelineEvent* timelineEvent)
	{
		Game::s_SceneManager->AddTimelineEvent(timelineName, timelineEvent);
	}

	void n2dStartTimeline(std::string timelineName)
	{
		Game::s_SceneManager->StartAndResetTimeline(timelineName);
	}

	void n2dRumble(int joystickID, float power, Uint32 durationMS)
	{
		Game::Rumble(joystickID, power, durationMS);
	}

	void n2dDirectorAddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float inOrDecreaseBy, float max, float* refVal)
	{
		Game::s_Director->AddToStack(left, page, labelText, labelWidth, inOrDecreaseBy, max, refVal);
	}

	void n2dDirectorAddToStackMinMax(bool left, BYTE page, std::string labelText,
		int labelWidth, float inOrDecreaseBy, float min, float max, float* minRefVal, float* maxRefVal)
	{
		Game::s_Director->AddToStackMinMax(left, page, labelText, labelWidth, inOrDecreaseBy, min, max, minRefVal, maxRefVal);
	}

	void n2dBlend(bool alpha)
	{
		Game::s_Renderer->SetBlendMode(alpha);
	}

	int n2dDebugDrawableCount()
	{
		return Game::s_Renderer->s_DrawLayers->GetInstanceCount();
	}

	int n2dDebugUpdaterCount()
	{
		return SceneManager::GetUpdaterCount();
	}

	int n2dDebugDeleteableCount()
	{
		return SceneManager::GetDeleteableCount();
	}

	int n2dDebugTimeEffectorsCount()
	{
		return Game::s_SceneManager->s_TimeEffectorManager->GetEffectorCount();
	}

	int n2dDebugTimeEffectedCount()
	{
		return Game::s_SceneManager->s_TimeEffectorManager->GetEffectedCount();
	}

	int n2dDebugReferencedCount()
	{
		return Game::s_SceneManager->s_ReferenceManager->GetReferenceCount();
	}

	int n2dDebugGraverCount()
	{
		return Game::s_SceneManager->s_GraverManager->GetGraverCount();
	}

	int n2dDebugTweenCount()
	{
		return Game::s_SceneManager->s_TweenManager->GetTweenCount();
	}

	unsigned int n2dTweenAdd(bool isFloat, void* propertyEffected, float start,
		float end, float durationMS, bool loop, bool autoDelete, TweenTypes type)
	{
		return Game::s_SceneManager->s_TweenManager->AddTween(isFloat, propertyEffected, start, end, durationMS, loop, autoDelete, type);
	}

	Tween& n2dTweenGet(unsigned int id)
	{
		return Game::s_SceneManager->s_TweenManager->GetTween(id);
	}

	void n2dTweenRemove(unsigned int id)
	{
		Game::s_SceneManager->s_TweenManager->RemoveTween(id);
	}

	void n2dTweenReset(unsigned int id)
	{
		Game::s_SceneManager->s_TweenManager->ResetTween(id);
	}

	void n2dTweenEnable(unsigned int id, bool enabled, bool reset)
	{
		Game::s_SceneManager->s_TweenManager->EnableTween(id, enabled, reset);
	}

	void n2dTweenSetLoopIndex(unsigned int tweenID, float valueBtw0And1)
	{
		Game::s_SceneManager->s_TweenManager->SetTweenLoopValue(tweenID, valueBtw0And1);
	}

	void n2dTweenSetDuration(unsigned int id, float durationMS)
	{
		Game::s_SceneManager->s_TweenManager->ResetDuration(id, durationMS);
	}








}