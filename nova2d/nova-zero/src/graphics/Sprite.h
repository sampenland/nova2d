#pragma once
#include "../core/Positional.h"
#include "../core/Deleteable.h"
#include "../core/Timer.h"
#include "Drawable.h"
#include <functional>

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace maths;
		
		class Sprite : public Positional, public Drawable, public Deleteable
		{
			
		private:

			SDL_Texture* m_SpriteSheet;
			std::string m_AssetName;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;

			bool m_Alive = true;

			bool m_AnimationRunning = false;
			bool m_AnimationLooping = false;
			int m_Frames = 1;
			int m_CurrentFrame = 0;
			Vec2Int m_FrameSize;

			Timer* m_AnimationTimer = nullptr;

			std::function<void(Sprite* sprite)> f_OnAnimationEnd;

		public:

			Sprite(std::string assetName, Vec2Int position, Vec2Int size, char layer);
			~Sprite();

			void ConfigureAnimating(bool isRunning) { m_AnimationRunning = true; }
			void ConfigureAnimation(int startFrame, int totalFrames, float animationSpeed, bool loop);
			void ConfigureAnimationEnd(std::function<void(Sprite* sprite)> f) { f_OnAnimationEnd = f; }
			void NextFrame();
			void JumpToFrame(int frame);

			void Update();
			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }
			void Draw() override;

			void DestroySelf();

			bool m_Visible = true;
			void ChangeLayer(char layer) { m_Layer = layer; }

			bool operator==(const Sprite& other);

		};
	}
}