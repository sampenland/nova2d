#pragma once
#include "../core/Defines.h"
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

			void AddSprite(Drawable* sprite, BYTE layer);
			void RemoveSprite(unsigned int id, BYTE layer);
			bool HasSpriteOnLayer(Drawable* sprite, const BYTE layer);

			void ClearSprites();

			void DrawLayer(const BYTE layer) const;
			void DrawAllLayers() const;

			static unsigned int s_TotalInstances;
			static unsigned int GetInstanceCount() { return s_TotalInstances; }

		};
	}
}