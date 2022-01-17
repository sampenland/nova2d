#pragma once
#include "../core/Positional.h"
#include "SDL_image.h"
#include "../core/Game.h"
#include "../core/Timer.h"

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
			
			Timer* m_NextFrameTimer = nullptr;

			bool m_AnimationRunning = false;
			int m_FrameWidth = 0;
			int m_FrameHeight = 0;
			int m_Frames = 1;
			int m_CurrentFrame = 0;

		public:

			Sprite(std::string assetName, Vec2Int position, Vec2Int frameSize, char layer);
			~Sprite();

			void ConfigureAnimating(bool isRunning) { m_AnimationRunning = isRunning; }
			void ConfigureAnimation(int frames, float delayBetweenFrames, bool looping);
			void NextFrame();
			void SetFrame(int frame);

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