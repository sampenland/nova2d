#include "TextureLoader.h"
#include "SDL_image.h"
#include "../logging/Logging.h"

namespace novazero
{
	namespace utils
	{
        using namespace logging;

        SDL_Texture* TextureLoader::Load(std::string path, SDL_Renderer& renderer)
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
                //Create texture from surface pixels
                newTexture = SDL_CreateTextureFromSurface(&renderer, loadedSurface);
                
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