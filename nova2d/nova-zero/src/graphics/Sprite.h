#pragma once
#include "../core/Positional.h"
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

			bool m_AnimationRunning = false;
			bool m_AnimationLooping = false;
			int m_Frames = 1;
			int m_CurrentFrame = 0;
			Vec2Int m_FrameSize;

			Timer* m_AnimationTimer = nullptr;

		public:

			Sprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			~Sprite();

			void ConfigureAnimating(bool isRunning) { m_AnimationRunning = true; }
			void ConfigureAnimation(int startFrame, int totalFrames, float animationSpeed, bool loop);
			void NextFrame();
			void JumpToFrame(int frame);

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