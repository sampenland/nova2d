#pragma once
#include "../core/Deleteable.h"
#include "../core/Timer.h"
#include "Drawable.h"
#include <functional>
#include "SDL.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace maths;
		
		class Sprite : public Drawable, public Deleteable
		{
			
		private:

			SDL_Texture* m_SpriteSheet;
			std::string m_AssetName;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;

			bool m_Alive = true;

			bool m_AnimationRunning = false;
			bool m_AnimationLooping = false;
			int m_StartFrame = 0;
			int m_Frames = 1;
			int m_AnimationLength = 1;
			int m_CurrentFrame = 0;
			SDL_RendererFlip m_Flip = SDL_FLIP_NONE;
			Vec2Int m_FrameSize;

			Timer* m_AnimationTimer = nullptr;

			std::function<void(Sprite* sprite)> f_OnAnimationEnd;

		public:

			Sprite(const std::string& assetName, Vec2 position, Vec2Int size, char layer);

			void ConfigureAnimating(bool isRunning) { m_AnimationRunning = true; }
			void ConfigureAnimation(int startFrame, int animationLength, int totalFrames, float animationSpeed, bool loop);
			void ConfigureAnimationEnd(std::function<void(Sprite* sprite)> f) { f_OnAnimationEnd = f; }
			void NextFrame();
			void JumpToFrame(int frame);

			void Update();

			void Flip(SDL_RendererFlip flip);

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }
			void Draw(float oX = 0.f, float oY = 0.f) override;

			void DestroySelf();

			bool m_Visible = true;
			void ChangeLayer(char layer) { m_Layer = layer; }

			bool operator==(const Sprite& other);

		};
	}
}