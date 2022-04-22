#pragma once
#include <vector>
#include "Sprite.h"
#include <cstring>
#include "../logging/logging.h"
#include "Drawable.h"
#include "../core/Camera.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;

		class DrawLayers
		{

		private:

			Camera* m_MainCamera = nullptr;
			std::vector<Drawable*> m_Layers[MAX_LAYERS + 1];

		public:

			DrawLayers();

			Camera* GetCamera() { return m_MainCamera; }

			void AddSprite(Drawable* sprite, unsigned char layer);
			void RemoveSprite(unsigned int id, unsigned char layer);
			bool HasSpriteOnLayer(Drawable* sprite, const unsigned char layer);

			void ClearSprites();

			void DrawLayer(const unsigned char layer) const;
			void DrawAllLayers() const;

			static unsigned int s_TotalInstances;
			static unsigned int GetInstanceCount() { return s_TotalInstances; }

		};
	}
}