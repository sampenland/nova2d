#pragma once

namespace novazero
{
	namespace core
	{
		// Max gamepads
		#define MAX_JOYSTICKS 8

		// Max draw layers
		#define MAX_LAYERS 20

		// Random int between min-max
		#define randomi(min, max) (int)(rand() % min + max)

		// Random float between min-max
		#define randomf(min, max) min + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(max - min)))
	}
}

/*
nova2d Add Updater(void(*f) funcToCall, context)
Updaters are called each frame; this adds a new funcToCall as an Updater
*/
#define n2dAddUpdater(funcToCall, context) novazero::core::SceneManager::AddUpdater(std::bind(&funcToCall, context));

/*
nova2d Remove Updater(void(*f) funcToRemove)
Updaters are called each frame; this removes a current updater function from updaters vector<void()>
*/
#define n2dRemoveUpdater(updaterToRemove, context) novazero::core::SceneManager::RemoveUpdater(std::bind(&updaterToRemove, context));

/*
nova2d Add Scene (std::string sceneName, Scene* scene)
Scenes are levels, menus, etc; this adds a scene to Game's Scene Manager
*/
#define n2dGameAddScene(sceneName, scene) novazero::core::Game::s_SceneManager->AddScene(sceneName, scene);

/*
nova2d Configure first game scene to start with (std::string sceneName)
Scenes are levels, menus, etc; this adds a scene to Game's Scene Manager
*/
#define n2dGameConfigFirstScene(sceneName) novazero::core::Game::s_SceneManager->ConfigureFirstScene(sceneName);

/*
nova2d Load and Add Texture (std::string assetName, std::string resourcePath)
Loads asset into Game's Asset Manager
*/
#define n2dAssetsLoadAndAddTexture(assetName, assetPath) novazero::core::Game::s_AssetManager->LoadAndAddTexture(assetName, assetPath);

/*
nova2d Add Color (std::string colorName, std::string colorHex, float alpha)
Adds Color to Game's Color Manager. ex: n2dAddColor("white", "ffffff", 1)
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
nova2d Add Drawable (Drawable* drawable, char layer)
Adds a graphic/drawable to Game's Draw Layers
*/
#define n2dAddDrawable(drawable, layer) novazero::core::Game::s_Renderer->s_DrawLayers->AddSprite(drawable, layer);

/*
nova2d Remove Drawable (Drawable* drawable, char layer)
Removes a graphic/drawable from Game's Draw Layers
*/
#define n2dRemoveDrawable(drawableID, layer) novazero::core::Game::s_Renderer->s_DrawLayers->RemoveSprite(drawableID, layer)