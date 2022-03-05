#include "AssetManager.h"
#include "../logging/logging.h"
#include "../utils/TextureLoader.h"

namespace novazero
{
	namespace utils
	{
		AssetManager::AssetManager() { }

		void AssetManager::LoadAndAddTexture(const std::string& name, std::string path)
		{
			SDL_Texture* texture = TextureLoader::Load(path);
			m_Textures[name] = texture;
		}

		void AssetManager::RemoveTexture(const std::string& name)
		{
			if (m_Textures.end() != m_Textures.find(name))
			{
				std::map<std::string, SDL_Texture*>::iterator f = m_Textures.find(name);
				m_Textures.erase(f);
			}
		}

		SDL_Texture* AssetManager::GetTexture(std::string name)
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

		void AssetManager::LoadAndAddMap(const std::string& name, std::string mapPath, const std::string& tilesetPath)
		{
			std::string tilesetName = name + "_tileset";
			m_Tilemaps[name] = new TiledMap(mapPath, tilesetName);
			LoadAndAddTexture(tilesetName, tilesetPath);
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

		TiledMap* AssetManager::GetMap(const std::string name)
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

			std::map<std::string, TiledMap*>::iterator it2;
			for (it2 = m_Tilemaps.begin(); it2 != m_Tilemaps.end(); it2++)
			{
				it2->second->DestroySelf();
			}

			m_Tilemaps.clear();
		}
	}
}