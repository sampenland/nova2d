#include "TextureLoader.h"
#include "SDL_image.h"
#include "../logging/Logging.h"
#include "../core/Game.h"

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
                LOG(path);
                LOG("SDL Image Load error.");
            }
            else
            {
                if (!Game::s_Renderer->GetSDLRenderer())
                {
                    LOG(path);
                    LOG("Game not initialize before loading texture");
                    return nullptr;
                }

                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface(Game::s_Renderer->GetSDLRenderer(), loadedSurface);
                
                if (newTexture == NULL)
                {
                    LOG(path);
                    LOG("SDL Texture create error.");
                }

                //Get rid of old loaded surface
                SDL_FreeSurface(loadedSurface);
            }

            return newTexture;
        }
	}
}