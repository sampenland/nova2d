#pragma once
#include "../core/Deleteable.h"
#include "../core/Timer.h"
#include "Drawable.h"
#include <functional>
#include <map>
#include "SDL.h"
#include "Drawable.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace maths;
		
		struct AnimStartEnd
		{
			unsigned short StartFrame = 0;
			unsigned short CurrentFrame = 0;
			unsigned short EndFrame = 0;
			float TimeBetweenFramesMS = 0.f;
			float CurrentFrameTime = 0.f;
			bool Loop = false;
			std::function<void(Sprite* sprite)> OnAnimationEnd = nullptr;
		};

		class Sprite : public Drawable, public Deleteable
		{
			
		private:

			SDL_Texture* m_SpriteSheet;
			std::string m_AssetName;

			// Animations ------------------------------
			std::string m_CurrentAnimation = "default";
			std::map<std::string, AnimStartEnd> m_Animations;
			bool m_AnimationRunning = false;

		public:

			void SwapTexture(const std::string& assetName);

			void Tint(const std::string& colorName);
			void ClearTint();

			void AddAnimation(const std::string& animName, unsigned short startFrame, unsigned short totalFrames,
				float timeBetweenFramesMS, bool loop, std::function<void(Sprite* sprite)> onComplete, bool makeActiveAnim = true);

			void ChangeAnimation(const std::string& animName, short frameOffset = 0);

			void DeleteAnimation(const std::string& animName);

			void StartAnimation();
			void StopAnimation();
			void JumpToFrame(unsigned short frame);
			void RestartAnimation();

			void TickAnimation();

			// ------------------------------------------

		private:

			bool m_AlphaChanging = false;
			float m_AlphaChangeSpeed = 0.25f;
			float m_PerciseAlpha = 255.f;
			Uint8 m_Alpha = 255;
			Uint8 m_StartAlpha = 255;
			Uint8 m_EndAlpha = 255;

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;
			float m_SpriteScale = 1.f;

			bool m_Alive = true;

			Vec2Int m_FrameSize;

		public:

			Sprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer, 
				float scale = 1.f, bool makeCopy = false);


			void Update();
			void ParticleUpdate(Vec2 newPosition);
			
			void SetScale(float scale);
			float GetScale() { return GetDrawScale(); }
			float* GetScaleRef() { return GetDrawScaleRef(); }

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }

			void OriginCenter() { GetDrawable()->OriginCenter(); }
			void SetOrigin(float x, float y) { GetDrawable()->SetOrigin(x, y); }
			void OriginTopLeft() { GetDrawable()->OriginTopLeft(); }

			float OffsetX() { return GetDrawable()->OffsetX(); }
			float OffsetY() { return GetDrawable()->OffsetY(); }

			/*
				Values 1 - 255
			*/
			void SetAlpha(Uint8 alpha);
			void ConfigureAlphaTween(Uint8 start, Uint8 end, float changeSpeed);

			void Draw(float oX = 0.f, float oY = 0.f, float scale = 1.f) override;

			void DestroySelf() override;
			
			void ChangeLayer(unsigned char layer) { m_Layer = layer; }

			bool operator==(const Sprite& other);

		};
	}
}