#pragma once
#include "../core/Positional.h"
#include "SDL_image.h"
#include "../maths/Vec2Int.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace maths;
		
		class Sprite : public Positional
		{
			
		private:

			SDL_Texture* m_SpriteSheet;
			std::string m_AssetName;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;

		public:

			Sprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			~Sprite();

			void Update();
			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }
			void Draw();

			bool m_Visible = true;
			void ChangeLayer(char layer) { m_Layer = layer; }

			bool operator==(const Sprite& other);

		public:

			unsigned int m_ID;
			char m_Layer;

		};
	}
}