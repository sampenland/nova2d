#include "NovaCore.hpp"
#include "Game.h"

namespace novazero
{
	unsigned int n2dGameGetID()
	{
		return Game::GetNextID();
	}

	bool n2dDebug()
	{
		Game::IsDebug();
	}

	void n2dDebugSet(bool isDebug)
	{
		Game::SetDebug(isDebug);
	}

	bool n2dDebugVerbose()
	{
		Game::IsDebugVerbose();
	}

	void n2dDebugVerboseSet(bool isDebug)
	{
		Game::SetDebugVerbose(isDebug);
	}

	float n2dDeltaTime()
	{
		return Game::GetDeltaTime();
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












}