#pragma once
#include "../core/Deleteable.h"
#include "../core/Timer.h"
#include "Drawable.h"
#include <functional>
#include <map>
#include "SDL.h"
#include "Drawable.h"
#include "../core/Referenceable.h"

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

		class Sprite : public Drawable, public Deleteable, public Referenceable
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

			SDL_Rect m_SrcRect;
			SDL_Rect m_DestRect;

			bool m_Alive = true;

			Vec2Int m_FrameSize;

		public:

			Sprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer,
				bool makeCopy = false);

			void Update();
			
			void SetScale(float scale);
			float GetScale() { return GetDrawScale(); }

			int GetWidth() const { return m_DestRect.w; }
			int GetHeight() const { return m_DestRect.h; }

			void OriginCenter() { GetDrawable()->OriginCenter(); }
			void SetOrigin(float x, float y) { GetDrawable()->SetOrigin(x, y); }
			void OriginTopLeft() { GetDrawable()->OriginTopLeft(); }

			float OffsetX() { return GetDrawable()->OffsetX(); }
			float OffsetY() { return GetDrawable()->OffsetY(); }

			void Draw(float oX = 0.f, float oY = 0.f, float scale = 1.f) override;

			void DestroySelf() override;
			
			void ChangeLayer(unsigned char layer) { m_Layer = layer; }

			bool operator==(const Sprite& other);

		};
	}
}