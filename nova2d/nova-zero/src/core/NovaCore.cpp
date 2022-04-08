#include "NovaCore.h"
#include "Game.h"
#include "../utils/ValueManager.h"
#include <functional>
#include "SDL.h"

namespace novazero
{
	namespace core
	{
		using namespace novazero::graphics;

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

		void n2dTweenReconfigure(unsigned int tweenID, float start,
			float end, float durationMS, bool loop, bool autoDelete)
		{
			Game::s_SceneManager->s_TweenManager->Reconfigure(tweenID, start, end, durationMS, loop, autoDelete);
		}

		void n2dScoreSet(unsigned int score)
		{
			Game::SetScore(score);
		}

		void n2dScoreAdd(unsigned int add)
		{
			Game::AddScore(add);
		}

		void n2dSQLScoreTableCreation(int nameMaxSize, int scoreDigitCount)
		{
			novazero::core::Game::s_SQLManager->CreateScoreTable(nameMaxSize, scoreDigitCount);
		}

		void n2dSQLScoreAdd(const std::string& playerName, int score)
		{
			novazero::core::Game::s_SQLManager->AddScore(playerName, score);
		}

		void n2dSQLScoreRemove(const std::string& playerName, int score)
		{
			novazero::core::Game::s_SQLManager->RemoveScore(playerName, score);
		}

		void n2dSQLScoreTopN(int count, std::vector<HighScore>& resultsOUT, unsigned long& lowestHighscoreOUT)
		{
			novazero::core::Game::s_SQLManager->GetScores(count, resultsOUT, lowestHighscoreOUT);
		}

		bool n2dIsKeyDown(SDL_KeyCode key)
		{
			return Game::s_InputHandler->IsKeyDown(key);
		}

		bool n2dIsKeyUp(SDL_KeyCode key)
		{
			return Game::s_InputHandler->IsKeyUp(key);
		}

		bool n2dIsJoyKeyDown(BYTE controllerID, int button)
		{
			return Game::s_InputHandler->IsJoystickButtonDown(controllerID, button);
		}

		bool n2dIsJoyKeyUp(BYTE controllerID, int button)
		{
			return Game::s_InputHandler->IsJoystickButtonUp(controllerID, button);
		}

		bool n2dJoyDPadLeft(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickHat(controllerID, SDL_HAT_LEFT);
		}

		bool n2dJoyDPadRight(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickHat(controllerID, SDL_HAT_RIGHT);
		}

		bool n2dJoyDPadUp(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickHat(controllerID, SDL_HAT_UP);
		}

		bool n2dJoyDPadDown(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickHat(controllerID, SDL_HAT_DOWN);
		}

		bool n2dJoySimpleLeft(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_LEFTX) < -novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoySimpleRight(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_LEFTX) > novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoySimpleUp(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_LEFTY) < -novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoySimpleDown(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_LEFTY) > novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoyRSimpleLeft(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_RIGHTX) < -novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoyRSimpleRight(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_RIGHTX) > novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoyRSimpleUp(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_RIGHTY) < -novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		bool n2dJoyRSimpleDown(BYTE controllerID)
		{
			return Game::s_InputHandler->GetJoystickAxis(controllerID, SDL_CONTROLLER_AXIS_RIGHTY) > novazero::core::Game::s_InputHandler->s_JoyStickDeadzone;
		}

		void n2dSQLConfigure(const std::string& databaseName, const std::string& connectionString, const std::string& user, const std::string& pass)
		{
			Game::s_SQLManager->Configure(databaseName, connectionString, user, pass);
		}

		void n2dTextInputClearBuffer(int newCharBufferMax)
		{
			novazero::core::Game::s_InputHandler->CleanTextBuffer(newCharBufferMax);
		}

		void n2dTextInputSetBuffer(std::string fillText, int maxChars)
		{
			novazero::core::Game::s_InputHandler->SetTextBuffer(fillText, maxChars);
		}

		SDL_Texture* n2dAssetsLoadAndAddTexture(const std::string& name, std::string path)
		{
			return Game::s_AssetManager->LoadAndAddTexture(name, path);
		}

		void n2dAssetsRemoveTexture(const std::string& name)
		{
			Game::s_AssetManager->RemoveTexture(name);
		}

		SDL_Texture* n2dAssetsGetTexture(const std::string& name)
		{
			return Game::s_AssetManager->GetTexture(name);
		}

		TiledMap* n2dAssetsLoadAndAddMap(const char* name, const char* mapPath, const char* tilesetImgPath, const char* tilesetPath)
		{
			return Game::s_AssetManager->LoadAndAddMap(name, mapPath, tilesetImgPath, tilesetPath);
		}

		TiledMap* n2dAssetsGetMap(std::string name)
		{
			return Game::s_AssetManager->GetMap(name);
		}

		void n2dGameAddScene(Scene* scene)
		{
			if (!Game::s_SceneManager)
			{
				LOG(LVL_FATAL_ERROR, "No Scene Manager. Are you adding a scene before creating your Game object?");
				Game::EndGame(ERR_NO_SCENE_MNGR);
				return;
			}

			Game::s_SceneManager->AddScene(scene->m_SceneName, scene);
		}

		void n2dGameConfigFirstScene(Scene* scene)
		{
			Game::s_SceneManager->ConfigureFirstScene(scene->m_SceneName);
		}

		Color* n2dAddColor(const char* colorName, std::string& hexCode, const Uint8 alpha)
		{
			return Game::s_ColorManager->AddColor(colorName, hexCode, alpha);
		}

		Color* n2dAddColor(const char* colorName, const char* hexCode, const Uint8 alpha)
		{
			return Game::s_ColorManager->AddColor(colorName, hexCode, alpha);
		}

		Color* n2dGetColor(const char* colorName)
		{
			return Game::s_ColorManager->GetColor(colorName);
		}

		Color* n2dGetColor(const std::string& colorName)
		{
			return Game::s_ColorManager->GetColor(colorName);
		}

		void n2dSetBackgroundColor(const char* colorName)
		{
			Game::s_Renderer->SetBackgroundColor(colorName);
		}

		void n2dRenderDrawColor(const char* colorName)
		{
			Game::s_Renderer->SetDrawColor(colorName);
		}

		void n2dRenderDrawColor(const std::string& colorName)
		{
			Game::s_Renderer->SetDrawColor(colorName.c_str());
		}

		Music* n2dLoadAndAddMusic(const std::string& assetName, const std::string& assetPath)
		{
			return Game::s_AudioManager->LoadAndAddMusic(assetName, assetPath);
		}

		SoundEffect* n2dLoadAndAddSoundEffect(const std::string& assetName, 
			const std::string& assetPath, int volume)
		{
			SoundEffect* se = Game::s_AudioManager->LoadAndAddSoundEffect(assetName, assetPath);
			
			if (!se) return nullptr;

			if (volume != 100)
			{
				se->SetVolume(volume);
			}
			return se;
		}

		void n2dAudioPlayOnce(bool isMusic, const std::string& assetName)
		{
			Game::s_AudioManager->PlayOnce(isMusic, assetName);
		}

		void n2dAudioLoop(bool isMusic, const std::string& assetName)
		{
			Game::s_AudioManager->Loop(isMusic, assetName);
		}

		void n2dAudioStop(bool isMusic, const std::string& assetName)
		{
			Game::s_AudioManager->Stop(isMusic, assetName);
		}

		b2World* n2dCurrentPhyWorld()
		{
			return Game::s_SceneManager->GetCurrentWorld();
		}

	}
}