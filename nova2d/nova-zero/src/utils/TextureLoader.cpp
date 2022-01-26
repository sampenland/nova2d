#include "TextureLoader.h"
#include "../core/Game.h"

#include "SDL_image.h"
#include "../logging/Logging.h"

namespace novazero
{
	namespace utils
	{
        using namespace logging;
        using namespace core;

        SDL_Texture* TextureLoader::Load(std::string path)
        {
            //The final texture
            SDL_Texture* newTexture = NULL;

            //Load image at specified path
            SDL_Surface* loadedSurface = IMG_Load(path.c_str());
            if (loadedSurface == NULL)
            {
                LOG(LVL_NON_FATAL_ERROR, "SDL Image Load error: " + path);
                LOG(LVL_NON_FATAL_ERROR, SDL_GetError());
                return nullptr;
            }
            else
            {
                if (!Game::s_Renderer->GetSDLRenderer())
                {
                    LOG(LVL_NON_FATAL_ERROR, "Game not initialize before loading texture: " + path);
                    return nullptr;
                }

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface(Game::s_Renderer->GetSDLRenderer(), loadedSurface);
                
                if (newTexture == NULL)
                {
                    LOG(LVL_FATAL_ERROR, "SDL Texture create error: " + path);
                    return nullptr;
                }

                //Get rid of old loaded surface
                SDL_FreeSurface(loadedSurface);
            }

            return newTexture;
        }
	}
}