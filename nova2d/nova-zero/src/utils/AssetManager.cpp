#include "AssetManager.h"

namespace novazero
{
	namespace utils
	{
		AssetManager::AssetManager() { }

		AssetManager::~AssetManager() 
		{
			std::map<std::string, SDL_Texture*>::iterator it;

			for (it = m_Textures.begin(); it != m_Textures.end(); it++)
			{
				SDL_DestroyTexture(m_Textures.at(it->first));
			}
		}

		void AssetManager::LoadAndAddTexture(std::string name, std::string path)
		{
			SDL_Texture* texture = TextureLoader::Load(path);
			m_Textures[name] = texture;
		}

		void AssetManager::RemoveTexture(std::string name)
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
				LOG(name);
				LOG("Cannot find texture");
				return nullptr;
			}
		}
	}
}