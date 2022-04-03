#include "AssetManager.h"
#include "../logging/logging.h"
#include "../utils/TextureLoader.h"
#include "../core/Game.h"

namespace novazero
{
	namespace utils
	{
		AssetManager::AssetManager() { }

		SDL_Texture* AssetManager::LoadAndAddTexture(const std::string& name, const std::string& path)
		{
			SDL_Texture* texture = TextureLoader::Load(path);
			m_Textures[name] = texture;
			return m_Textures[name];
		}

		void AssetManager::RemoveTexture(const std::string& name)
		{
			if (m_Textures.end() != m_Textures.find(name))
			{
				std::map<std::string, SDL_Texture*>::iterator f = m_Textures.find(name);
				
				SDL_DestroyTexture(m_Textures.at(name));

				m_Textures.erase(f);
			}
		}

		SDL_Texture* AssetManager::GetTexture(const std::string& name)
		{
			try
			{
				return m_Textures.at(name);
			}
			catch (const std::out_of_range& oor)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot find texture: " + name);
				LOG(LVL_NON_FATAL_ERROR, oor.what());
				return nullptr;
			}
		}

		SDL_Texture* AssetManager::GetTextureCopy(const std::string& name)
		{
			
			try
			{
				SDL_Point size;
				SDL_QueryTexture(m_Textures.at(name), NULL, NULL, &size.x, &size.y);
								
				SDL_Texture* copy = SDL_CreateTexture(Game::s_Renderer->GetSDLRenderer(),
					SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, size.x, size.y);

				SDL_SetTextureBlendMode(copy, SDL_BLENDMODE_BLEND);
				SDL_SetRenderTarget(Game::s_Renderer->GetSDLRenderer(), copy);

				SDL_Rect tileDestRect;
				tileDestRect.x = 0;
				tileDestRect.y = 0;
				tileDestRect.w = size.x;
				tileDestRect.h = size.y;

				SDL_RenderCopy(Game::s_Renderer->GetSDLRenderer(), m_Textures.at(name),
					NULL, &tileDestRect);

				// Reset renderer
				SDL_SetRenderTarget(Game::s_Renderer->GetSDLRenderer(), NULL);

				return copy;
				
			}
			catch (const std::out_of_range& oor)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot find texture: " + name);
				LOG(LVL_NON_FATAL_ERROR, oor.what());
				return nullptr;
			}
		}

		TiledMap* AssetManager::LoadAndAddMap(const std::string& name, const std::string& mapPath, const std::string& tilesetImgPath, const std::string& tilesetPath)
		{
			m_Tilemaps[name] = new TiledMap(mapPath, tilesetImgPath, tilesetPath);
			return m_Tilemaps[name];
		}

		void AssetManager::RemoveMap(const std::string& name)
		{
			if (m_Tilemaps.end() != m_Tilemaps.find(name))
			{
				std::map<std::string, TiledMap*>::iterator f = m_Tilemaps.find(name);
				f->second->DestroySelf();
				m_Tilemaps.erase(f);
			}
		}

		TiledMap* AssetManager::GetMap(const std::string& name)
		{
			try
			{
				return m_Tilemaps.at(name);
			}
			catch (const std::out_of_range& oor)
			{
				LOG(LVL_NON_FATAL_ERROR, "Cannot find tilemap: " + name);
				LOG(LVL_NON_FATAL_ERROR, oor.what());
				return NULL;
			}
		}

		void AssetManager::DestroySelf()
		{
			std::map<std::string, SDL_Texture*>::iterator it;

			for (it = m_Textures.begin(); it != m_Textures.end(); it++)
			{
				SDL_DestroyTexture(m_Textures.at(it->first));
			}

			m_Textures.clear();
			m_Tilemaps.clear();
		}
	}
}