#pragma once

// nova2d Version	
#define NOVA_VERSION "0.0.05"

// ------------------------------
// RAW VARIABLES
// ------------------------------

// Pointer to main (only as of now) camera
#define CAMERA novazero::core::Game::GetCamera()
#define CAMERA_ZOOM novazero::core::Game::GetCamera()->GetZoom()
#define CAMERA_SCALE novazero::core::Game::GetCamera()->GetScale()

// Max gamepads
#define MAX_JOYSTICKS 4

// Max draw layers
#define MAX_LAYERS 255
#define PERSISTENT_LAYER 254

// Tilemap draw layer
#define TILEMAP_DRAW_LAYER -1

// Max director pages
#define MAX_DIRECTOR_PAGES 20

// Max left and right slots on director
#define MAX_DIRECTOR_SLOTS 8

// Max graver groups
#define MAX_GRAVER_GROUPS 255

// Max particles
#define MAX_PARTICLES 255

#define PI (float)(2*acos(0.0))

#define BYTE unsigned char

#define tostring(v) std::to_string(v)

// ---------------------
// Quick Acess
// ---------------------

#define n2dDebug Game::IsDebug()
#define n2dDebugVerbose Game::IsDebugVerbose()

/*
nova2d Get Delta Time
Returns time between frames
*/
#define n2dDeltaTime Game::GetDeltaTime()

/*
nova2d Get Time Scale
Returns a float value which directly effects all moving objects
*/
#define n2dTimeScale novazero::core::Game::s_TimeScale

/*
nova2d Coin Flip ()
Simply returns heads/tails (true or false) : 50% chance
*/
#define n2dCoinFlip() novazero::core::Game::CoinFlip()

/*
nova2d Round To Even (number)
*/
#define n2dRoundEven(num) (num % 2 == 0) ? num : (num + 1)

/*
nova2d make func
Binds to make a func pointer
*/
#define n2dMakeFunc(func, context) std::bind(&func, context)
#define n2dMakeFuncArgs1(func, context, a1) std::bind(&func, context, std::placeholders::_1)
#define n2dMakeFuncArgs2(func, context, a1, a2) std::bind(&func, context, std::placeholders::_1, std::placeholders::_2)
#define n2dMakeFuncArgs3(func, context, a1, a2, a3) std::bind(&func, context, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
#define n2dMakeFuncArgs4(func, context, a1, a2, a3, a4) std::bind(&func, context, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)
#define n2dMakeFuncArgs5(func, context, a1, a2, a3, a4, a5) std::bind(&func, context, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5)

/*
nova2d Random Float (float min, float max)
Returns a random float in range
*/
#define n2dRandomFloat(min, max) novazero::core::Game::RandomFloat(min, max)

/*
nova2d Random Float with MAX chance(float min, float max, 0-1 percent chance of MAX)
Returns a random float in range with a likeliness of hitting MAX
*/
#define n2dRandomFloatMaxChance(min, max, chanceOfMax) novazero::core::Game::RandomFloatWithMaxChance(min, max, chanceOfMax);
/*
nova2d Random Float with MIN chance(float min, float max, 0-1 percent chance of MIN)
Returns a random float in range with a likeliness of hitting MIN
*/
#define n2dRandomFloatMinChance(min, max, chanceOfMin) novazero::core::Game::RandomFloatWithMinChance(min, max, chanceOfMin);

/*
nova2d Random Int (int min, int max)
Returns a random integer in range
*/
#define n2dRandomInt(min, max) novazero::core::Game::RandomInt(min, max);

/*
nova2d Random Int with MAX chance (int min, int max, float 0-1 percent chance of MAX)
Returns a random integer in range with a chance of hitting MAX
*/
#define n2dRandomIntMaxChance(min, max, chanceOfMax) novazero::core::Game::RandomIntWithMaxChance(min, max, chanceOfMax);

/*
nova2d Random Int with MIN chance (int min, int max, float 0-1 percent chance of MIN)
Returns a random integer in range with a chance of hitting MIN
*/
#define n2dRandomIntMinChance(min, max, chanceOfMin) novazero::core::Game::RandomIntWithMaxChance(min, max, chanceOfMin);

/*
nova2d Global Game Score ()
Easy access globally to game score
*/
#define n2dScore novazero::core::Game::GetScore()

// ------------------------------------------------------------------------

#include "SDL.h"
#include "../utils/timeline/TimelineEvent.h"
#include "../utils/Tweens.h"
#include "../utils/TweenManager.h"

#include <string>
#include <cmath>

namespace novazero
{
	namespace core
	{
		using namespace novazero::utils;
		using namespace novazero::utils::timeline;


		// ----------------------------------------------------------------------------

		/*
		nova2d Get Unique Game ID
		Returns a unique unsigned int ID value
		*/
		unsigned int n2dGameGetID();

		void n2dDebugSet(bool isDebug);
		void n2dDebugVerboseSet(bool isDebug);

		/*
		nova2d Set Time Scale (float value)
		Sets a float value which directly effects all moving objects
		*/
		void n2dTimeScaleSet(float timeScale);

		/*
		nova2d Set camera zoom level
		Sets main internal camera Zoom Level
		*/
		void n2dZoomCamera(float zoomLevel);

		/*
		nova2d Enable free move
		Basic movement; normally used for testing
		*/
		void n2dEnableCameraFreeMove(bool enabled);

		/*
		nova2d Pause Game (bool pause)
		*/
		void n2dPauseGame(bool pause);

		/*
		nova2d Set Pause key (SDL_KeyCode key)
		*/
		void n2dPauseKeySet(SDL_KeyCode key);
		void n2dPauseKeyClear();

		//----------------------------------------------------------------------------
		// VALUE MANAGER
		//----------------------------------------------------------------------------

		/*
		nova2d Value Add (std::string, float, bool persistent)
		Adds a global variable which can be grabbed from anywhere in your code
		RETURNS float* to value
		*/
		float* n2dValueManagerAdd(std::string name, float value, bool persist);

		/*
		nova2d Value Get
		Gets a previously added variable
		*/
		float n2dValueManagerGet(std::string name);

		/*
		Gets a reference to a previously added variable
		THIS can be used for tweens, Director stackables, etc.
		*/
		float* n2dValueManagerGetRef(std::string name);

		//----------------------------------------------------------------------------
		// TIMELINES
		//----------------------------------------------------------------------------

		/*
		nova2d Add to timeline (string timelineName, TimelineEvent event)
		Add's a timeline event to a timeline
		TimelineEvent is the base class of TimelineCreateEvent, TimelineExecuteEvent
		*/
		void n2dAddTimeline(std::string timelineName, TimelineEvent* timelineEvent);

		/*
		nova2d Starts a timeline with a certain name
		Timeline must exists
		*/
		void n2dStartTimeline(std::string timelineName);
		
		//----------------------------------------------------------------------------
		// DIRECTOR
		//----------------------------------------------------------------------------

		/*
		n2d Director AddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float inOrDecreaseBy, float max, float* refVal)
		Adds a persistent ScrollSelect to Director's page Left/Right stacks
		*/
		void n2dDirectorAddToStack(bool left, BYTE page, std::string labelText, int labelWidth, float inOrDecreaseby, float max, float* refVal);

		/*
		n2d Director AddToStackMinMax(bool left, BYTE page, std::string labelText, int labelWidth, float inOrDecreaseBy, float min, float max, float* minRefVal, float* maxRefVal)
		Adds a persistent ScrollSelect to Director's page Left/Right stacks
		*/
		void n2dDirectorAddToStackMinMax(bool left, BYTE page, std::string labelText,
			int labelWidth, float inOrDecreaseby, float min, float max, float* minRefVal, float* maxRefVal);

		//----------------------------------------------------------------------------
		// DEBUG
		//----------------------------------------------------------------------------

		/*
		nova2d Get total instances
		Returns total drawables on screen
		*/
		int n2dDebugDrawableCount();

		/*
		nova2d Get total updaters
		Returns total updaters in Game processor
		*/
		int n2dDebugUpdaterCount();

		/*
		nova2d Get total deleteables
		Returns total deleteables (similar to drawables)
		*/
		int n2dDebugDeleteableCount();

		/*
		nova2d Get total time effectors
		Returns total time effectors (similar to gravers)
		*/
		int n2dDebugTimeEffectorsCount();

		/*
		nova2d Get total time effecteds
		Returns total time effected objects (similar to effectors)
		*/
		int n2dDebugTimeEffectedCount();

		/*
		nova2d Get total referenced
		Returns total referenced objs (similar to deletables)
		*/
		int n2dDebugReferencedCount();

		/*
		nova2d Get total gravers
		Returns total graver objs (similar to colliders)
		*/
		int n2dDebugGraverCount();

		/*
		nova2d Get total tweens
		Returns total tweens (usually attached to positionals)
		*/
		int n2dDebugTweenCount();

		//----------------------------------------------------------------------------
		// GRAPHICS
		//----------------------------------------------------------------------------

		/*
		nova2d Renderer Blend Modes (bool alpha)
		Enables alpha blending if needed
		*/
		void n2dBlend(bool alpha);

		//----------------------------------------------------------------------------
		// TWEENS
		//----------------------------------------------------------------------------

		/*
		nova2d Add Tween Float *ref, start, end, duration, loop, auto delete, TweenType::
		Tweens *refFloat (referenced float) from start to end in duration milliseconds
		RETURNS ID for clean up
		*/
		unsigned int n2dTweenAdd(bool isFloat, void* propertyEffected, float start,
			float end, float durationMS, bool loop, bool autoDelete, TweenTypes type);

		/*
		nova2d GetTween(unsigned int id)
		Gets a created tween from game's tween manager
		RETURNS tween reference
		*/
		Tween& n2dTweenGet(unsigned int id);

		/*
		nova2d Remove Tween (unsigned int tweenID)
		Remove a tween
		*/
		void n2dTweenRemove(unsigned int id);

		/*
		nova2d Restart Tween (unsigned int tweenID)
		Restart a tween
		*/
		void n2dTweenReset(unsigned int id);

		/*
		nova2d Enable/disable Tween (unsigned int tweenID)
		Enable/disable a tween
		*/
		void n2dTweenEnable(unsigned int id, bool enabled, bool reset);

		/*
		nova2d Set Loop Index For Tween (unsigned int tweenID, loopIDX)
		Sets the value for when a tween hits the end and is set to loop
		*/
		void n2dTweenSetLoopIndex(unsigned int tweenID, float valueBtw0And1);

		/*
		nova2d Resets duration for tween (unsigned int tweenID, newDurationMS)
		Sets the value for when a tween hits the end and is set to loop
		*/
		void n2dTweenSetDuration(unsigned int id, float durationMS);

		/*
		nova2d Reconfigure Tween (unsigned int tweenID, float start, float end,
		float durationMS, bool loop, bool autodelete)
		Reset/reconfigure a tween with an id
		*/
		void n2dTweenReconfigure(unsigned int tweenID, float start,
			float end, float durationMS, bool loop, bool autoDelete);

		//----------------------------------------------------------------------------
		// nova Scoring
		//----------------------------------------------------------------------------

		/*
		nova2d Global Game Score ()
		Easy access globally to game score
		*/
		void n2dScoreSet(unsigned int score);

		/*
		nova2d Global Game Score ()
		Easy access globally to game score
		*/
		void n2dScoreAdd(unsigned int add);

		//----------------------------------------------------------------------------
		// INPUT
		//----------------------------------------------------------------------------
		// ------- JOYSTICKS/CONTROLLERS
		
		/*
		nova2d Rumble (int joystickID, float 0-1 power, Uint32 durationMS)
		Rumble the controller at power for duration milliseconds
		*/
		void n2dRumble(int joystickID, float power, Uint32 durationMS);

		// ------- KEYS
		/*
		nova2d Is key down (SDL_Keycode key)
		Returns realtime if key is pressed down
		*/
		bool n2dIsKeyDown(SDL_KeyCode key);

		/*
		nova2d Is key up (SDL_Keycode key)
		Returns realtime if key is up
		*/
		bool n2dIsKeyUp(SDL_KeyCode key);

		/*
		nova2d Is key down (joystickID, button)
		Returns realtime if key is pressed down
		*/
		bool n2dIsJoyKeyDown(BYTE controllerID, int button);

		/*
		nova2d Is key up (joystickID, button)
		Returns realtime if key is not pressed
		*/
		bool n2dIsJoyKeyUp(BYTE controllerID, int button);

		/*
		nova2d JoyDPad Left pressed down
		*/
		bool n2dJoyDPadLeft(BYTE controllerID);

		/*
		nova2d JoyDPad Right pressed down
		*/
		bool n2dJoyDPadRight(BYTE controllerID);

		/*
		nova2d JoyDPad Up pressed down
		*/
		bool n2dJoyDPadUp(BYTE controllerID);

		/*
		nova2d JoyDPad Down pressed down
		*/
		bool n2dJoyDPadDown(BYTE controllerID);

		/*
		nova2d Joy Simple Direction means joy is mostly left on axis
		*/
		bool n2dJoySimpleLeft(BYTE controllerID);

		/*
		nova2d Joy Simple Direction means joy is mostly right on axis
		*/
		bool n2dJoySimpleRight(BYTE controllerID);

		/*
		nova2d Joy Simple Direction means joy is mostly up on axis
		USES InputHandler::s_JoyStickDeadzone
		*/
		bool n2dJoySimpleUp(BYTE controllerID);

		/*
		nova2d Joy Simple Direction means joy is mostly down on axis
		*/
		bool n2dJoySimpleDown(BYTE controllerID);

		/*
		nova2d RIGHT Joy Simple Direction means joy is mostly left on axis
		*/
		bool n2dJoyRSimpleLeft(BYTE controllerID);

		/*
		nova2d RIGHT Joy Simple Direction means joy is mostly right on axis
		*/
		bool n2dJoyRSimpleRight(BYTE controllerID);

		/*
		nova2d RIGHT Joy Simple Direction means joy is mostly up on axis
		USES InputHandler::s_JoyStickDeadzone
		*/
		bool n2dJoyRSimpleUp(BYTE controllerID);

		/*
		nova2d RIGHT Joy Simple Direction means joy is mostly down on axis
		*/
		bool n2dJoyRSimpleDown(BYTE controllerID);




	}
}








/*
nova2d SQL Configure(std::string connectionString, std::string table, std::string user, std::string pass)
Enables SQL use
*/
#define n2dSQLConfigure(connectionString, table, user, pass) novazero::core::Game::s_SQLManager->Configure(connectionString, table, user, pass);

/*
nova2d SQL Scores Create Table (int, int)
Creates simple nova2d highscores table
*/
#define n2dSQLScoreTableCreation(nameCharCount, scoreDigitCount) novazero::core::Game::s_SQLManager->CreateScoreTable(nameCharCount, scoreDigitCount);

/*
nova2d SQL Scores Add (string int)
Inserts new score into nova2d's simple highscore table
*/
#define n2dSQLScoreAdd(playerName, score) novazero::core::Game::s_SQLManager->AddScore(playerName, score);

/*
nova2d SQL Scores Remove (string, int)
Removes score from nova2d's simple highscore table
*/
#define n2dSQLScoreRemove(playerName, score) novazero::core::Game::s_SQLManager->RemoveScore(playerName, score);

/*
nova2d SQL Get Scores (count, &results, &lowestScore)
Grabs top N amount of scores
*/
#define n2dSQLScoreTopN(count, results, lowest) novazero::core::Game::s_SQLManager->GetScores(count, results, lowest);

/*
nova2d Clear Text edit buffer (limitSizeOfBuffer)
Clears textbox input buffer
*/
#define n2dTextInputClearBuffer(newBufferMax) novazero::core::Game::s_InputHandler->CleanTextBuffer(newBufferMax);

/*
nova2d Set Text edit buffer (limitSizeOfBuffer)
Sets text in input buffer
*/
#define n2dTextInputSetBuffer(fillText, maxChars) novazero::core::Game::s_InputHandler->SetTextBuffer(fillText, maxChars);

/*
nova2d Add Key Down Listener (SDL_KeyCode key, void() function, context)
Calls function on SDL_KeyCode key down
Must be called on in a class that inherits from EventListener
*/
#define n2dAddKeyDownListener(key, func, context) AddKeysEventListener(key, &InputHandler::IsKeyDown, std::bind(&func, context));

/*
nova2d Remove Key Down Listener (SDL_KeyCode key)
Removes previously added key down listener attached to SLD_KeyCode key
Must be called on in a class that inherits from EventListener
*/
#define n2dRemoveKeyDownListener(key) RemoveEventListener(key);

/*
nova2d Add Joystick Key Down Listener (int joystickID, int button, f_JoyStickConditionalFunction conditionalFunction, f_VoidFunction executeFunction)
Calls function on SDL_CONTOLLER_BUTTON key down
Must be called on in a class that inherits from EventListener
*/
#define n2dAddJoyKeyDownListener(joystickID, button, func, context) AddJoyEventListener(joystickID, button, &InputHandler::IsJoystickButtonDown, std::bind(&func, context))

/*
nova2d Remove Key Down Listener (int joystickID, int button)
Removes previously added key down listener attached to SDL_CONTROLLER BUTTON
Must be called on in a class that inherits from EventListener
*/
#define n2dRemoveJoyKeyDownListener(joystickID, button) RemoveJoyEventListener(joystickID, button)

/*
nova2d Add Key Up Listener (SDL_CONTROLLER_BUTTON button, void() function, context)
Calls function on SDL_KeyCode key up
Must be called on in a class that inherits from EventListener
*/
#define n2dAddJoyKeyUpListener(joystickID, button, func, context) AddJoyEventListener(joystickID, button, &InputHandler::IsJoystickButtonUp, std::bind(&func, context))

/*
nova2d Remove Key Up Listener (SDL_KeyCode key)
Removes previously added key up listener attached to SLD_KeyCode key
Must be called on in a class that inherits from EventListener
*/
#define n2dRemoveJoyUpListener(joystickID, button) RemoveJoyEventListener1(joystickID, button);

/*
nova2d Add Key Up Listener (SDL_KeyCode key, void() function, context)
Calls function on SDL_KeyCode key up
Must be called on in a class that inherits from EventListener
*/
#define n2dAddKeyUpListener(key, func, context) AddKeysEventListener1(key, &InputHandler::IsKeyUp, std::bind(&func, context));

/*
nova2d Remove Key Up Listener (SDL_KeyCode key)
Removes previously added key up listener attached to SLD_KeyCode key
Must be called on in a class that inherits from EventListener
*/
#define n2dRemoveKeyUpListener(key) RemoveEventListener1(key);

/*
nova2d Add Updater(void(*f) funcToCall, context)
Updaters are called each frame; this adds a new funcToCall as an Updater
REQUIRES: sceneManager include
RETURNS unsigned int CleanID
*/
#define n2dAddUpdater(funcToCall, context) novazero::core::SceneManager::AddUpdater(std::bind(&funcToCall, context))

/*
nova2d Add a Persistent Updater(void(*f) funcToCall, context)
Updaters are called each frame; this adds a new funcToCall as an Updater
(PERSISTENT MEANS this will remain in game until removed manually)
RETURNS unsigned int CleanID
*/
#define n2dAddUpdaterPersistent(funcToCall, context) novazero::core::SceneManager::AddPersistentUpdater(std::bind(&funcToCall, context));

/*
nova2d Remove Updater(void(*f) funcToRemove)
Updaters are called each frame; this removes a current updater function from updaters vector<void()>
*/
#define n2dRemoveUpdater(id) novazero::core::SceneManager::RemoveUpdater(id);

/*
nova2d Add Scene (std::string sceneName, Scene* scene)
Scenes are levels, menus, etc; this adds a scene to Game's Scene Manager
*/
#define n2dGameAddScene(scene) novazero::core::Game::s_SceneManager->AddScene(scene->m_SceneName, scene);

/*
nova2d Configure first game scene to start with (std::string sceneName)
Scenes are levels, menus, etc; this adds a scene to Game's Scene Manager
*/
#define n2dGameConfigFirstScene(scene) novazero::core::Game::s_SceneManager->ConfigureFirstScene(scene->m_SceneName);

/*
nova2d Load and Add Texture (std::string assetName, std::string resourcePath)
Loads asset into Game's Asset Manager
*/
#define n2dAssetsLoadAndAddTexture(assetName, assetPath) novazero::core::Game::s_AssetManager->LoadAndAddTexture(assetName, assetPath);

/*
nova2d Get Texture by name (std::string textureName)
Return pointer to a preloaded texture
*/
#define n2dAssetsGetTexture(textureName) novazero::core::Game::s_AssetManager->GetTexture(textureName);

/*
nova2d Load Tilemap (std::string& name, std::string mapPath, std::string& tilesetImgPath, std::string& tilesetPath)
Loads map into Game's asset manager
*/
#define n2dAssetsLoadAndAddMap(mapName, mapPath, tilesetImgPath, tilesetPath)  novazero::core::Game::s_AssetManager->LoadAndAddMap(mapName, mapPath, tilesetImgPath, tilesetPath);

/*
nova2d Get Tilemap by name (std::string mapName)
Return pointer to a preloaded tiled map
*/
#define n2dAssetsGetMap(mapName) novazero::core::Game::s_AssetManager->GetMap(mapName);


/*
nova2d Add Color (std::string colorName, std::string colorHex, float alpha(0-255))
Adds Color to Game's Color Manager. ex: n2dAddColor("white", "ffffff", 255)
*/
#define n2dAddColor(colorName, hexCode, alpha) novazero::core::Game::s_ColorManager->AddColor(colorName, hexCode, alpha);

/*
nova2d Get Color (std::string colorName)
Gets Color from Game's Color Manager
*/
#define n2dGetColor(colorName) novazero::core::Game::s_ColorManager->GetColor(colorName);

/*
nova2d SetBackgroundColor(std::string colorName)
Sets default background to a color already loaded in Game's Color Manager
*/
#define n2dSetBackgroundColor(colorName) novazero::core::Game::s_Renderer->SetBackgroundColor(colorName);

/*
nova2d Change Scene(std::string sceneName)
Changes to Game's Scene Manager preloaded scene
*/
#define n2dSceneChange(sceneName) novazero::core::Game::s_SceneManager->ChangeScene(sceneName);

/*
nova2d Set draw color (std::string colorName)
Updates SDL renderer's draw color from preloaded Game's Color Manager's color
*/
#define n2dRenderDrawColor(colorName) novazero::core::Game::s_Renderer->SetDrawColor(colorName);

/*
nova2d Add deleteable
Adds a Deleteable* to Game's Scene Manager's deleteable tracker
RETURNS an unsigned int ID of deleteable for cleanup
*/
#define n2dAddDeleteable(deleteable) novazero::core::Game::s_SceneManager->AddDeleteable(deleteable);

/*
nova2d Remove deleteable
Removes a Deleteable* to Game's Scene Manager's deleteable tracker
*/
#define n2dRemoveDeleteable(id) novazero::core::Game::s_SceneManager->RemoveDeleteable(id);

/*
nova2d Add Drawable (Drawable* drawable, unsigned char layer)
Adds a graphic/drawable to Game's Draw Layers
RETURNS: void
*/
#define n2dAddDrawable(drawable, layer) novazero::core::Game::s_Renderer->s_DrawLayers->AddSprite(drawable, layer);

/*
nova2d Remove Drawable (Drawable* drawable, unsigned char layer)
Removes a graphic/drawable from Game's Draw Layers
*/
#define n2dRemoveDrawable(drawableID, layer) novazero::core::Game::s_Renderer->s_DrawLayers->RemoveSprite(drawableID, layer)

/*
nova2d Add Reference (std::string referenceName, Referenceable* reference)
Adds a reference to Referenceable object into Game's Reference Manager
*/
#define n2dReferenceAdd(referenceName, reference) novazero::core::SceneManager::s_ReferenceManager->AddReference(referenceName, reference);

/*
nova2d Get Reference (std::string referenceName)
Gets a reference to Referenceable object from Game's Reference Manager
*/
#define n2dReferenceGet(referenceName) novazero::core::SceneManager::s_ReferenceManager->GetReferenced(referenceName);

/*
nova2d Remove Reference (std::string referenceName)
Removes a reference from Game's Reference Manager
*/
#define n2dReferenceRemove(referenceName) novazero::core::SceneManager::s_ReferenceManager->RemoveReference(referenceName);

/*
nova2d Add Font (std::string fontName, std::string fontPath, int fontSize)
Adds font to Game's Font Manager
*/
#define n2dFontAdd(fontName, fontPath, fontSize) novazero::core::Game::s_FontManager->AddFont(fontName, fontPath, fontSize);

/*
nova2d Get Font (std::string fontName)
Adds font to Game's Font Manager
*/
#define n2dFontGet(fontName) novazero::core::Game::s_FontManager->GetFont(fontName);