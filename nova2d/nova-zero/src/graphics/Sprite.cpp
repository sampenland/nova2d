#include "Sprite.h"

#include "../utils/TextureLoader.h"
#include "../logging/Logging.h"
#include "SDL_image.h"
#include "../core/Game.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace utils;
		using namespace logging;

		Sprite::Sprite(const std::string& assetName, Vec2 position, Vec2Int size, char layer)
			: Deleteable(assetName), m_SrcRect(SDL_Rect()), m_DestRect(SDL_Rect())
		{
			SetPosition(position);
			SetSize(size);

			m_Angle = 0;
			m_Layer = layer;
			
			m_AssetName = assetName;
			m_SpriteSheet = Game::s_AssetManager->GetTexture(assetName);
			m_FrameSize = size;

			// Draw setup
			m_SrcRect.x = 0;
			m_SrcRect.y = 0;
			m_SrcRect.w = (int)size.x;
			m_SrcRect.h = (int)size.y;
			m_DestRect.w = (int)size.x;
			m_DestRect.h = (int)size.y;

			// Setup a default 1 frame animation
			AddAnimation("default", 0, 1, 0, false, nullptr, true);
			m_CleanUpdaters.push_back(n2dAddUpdater(Sprite::TickAnimation, this));

			LinkPositionalSprite(this);

			// Final
			m_ID = Game::GetNextID();
			n2dAddDrawable(this, m_Layer);
		}

		// Animations -------------------------------

		void Sprite::AddAnimation(const std::string& animName, unsigned short startFrame, unsigned short totalFrames,
			float timeBetweenFramesMS, bool loop, std::function<void(Sprite* sprite)> onComplete, bool makeActiveAnimation)
		{
			AnimStartEnd data;
			data.StartFrame = startFrame;
			data.EndFrame = startFrame + (totalFrames - 1);
			data.TimeBetweenFramesMS = timeBetweenFramesMS;
			data.CurrentFrameTime = 0;
			data.Loop = loop;
			data.OnAnimationEnd = onComplete;

			if (m_Animations.find(animName) != m_Animations.end())
			{
				LOG(LVL_W, animName + " already exists in animations. OVERWRITING!");
			}

			m_Animations[animName] = data;

			if (makeActiveAnimation)
			{
				m_CurrentAnimation = animName;
				m_AnimationRunning = true;
			}

		}

		void Sprite::ChangeAnimation(const std::string& animName, short frameOffset)
		{
			if (m_CurrentAnimation == animName)
			{
				if (frameOffset > 0)
				{
					if (m_Animations[animName].StartFrame + frameOffset <= m_Animations[animName].EndFrame)
					{
						m_Animations[animName].CurrentFrame = m_Animations[animName].StartFrame + frameOffset;
						m_Animations[animName].CurrentFrameTime = m_Animations[animName].TimeBetweenFramesMS;
					}
				}

				return;
			}

			if (m_Animations.find(animName) != m_Animations.end())
			{
				m_CurrentAnimation = animName;

				if (frameOffset > 0)
				{
					if (m_Animations[animName].StartFrame + frameOffset <= m_Animations[animName].EndFrame)
					{
						m_Animations[animName].CurrentFrame = m_Animations[animName].StartFrame + frameOffset;
						m_Animations[animName].CurrentFrameTime = m_Animations[animName].TimeBetweenFramesMS;
					}
					else
					{
						LOG(LVL_W, "Sprite's frame offset over-runs sprite's anaimation frames");
					}
				}
			}
		}

		void Sprite::DeleteAnimation(const std::string& animName)
		{
			m_Animations.erase(animName);
		}

		void Sprite::StartAnimation()
		{
			m_AnimationRunning = true;
		}

		void Sprite::StopAnimation()
		{
			m_AnimationRunning = false;
		}

		void Sprite::JumpToFrame(unsigned short frame)
		{
			unsigned short animationFrame = m_Animations[m_CurrentAnimation].StartFrame + frame;
			if (animationFrame < m_Animations[m_CurrentAnimation].EndFrame)
			{
				m_Animations[m_CurrentAnimation].CurrentFrame = animationFrame;
				m_Animations[m_CurrentAnimation].CurrentFrameTime = m_Animations[m_CurrentAnimation].TimeBetweenFramesMS;
			}
		}

		void Sprite::RestartAnimation()
		{
			m_Animations[m_CurrentAnimation].CurrentFrame = m_Animations[m_CurrentAnimation].StartFrame;
			m_Animations[m_CurrentAnimation].CurrentFrameTime = m_Animations[m_CurrentAnimation].TimeBetweenFramesMS;
		}

		void Sprite::TickAnimation()
		{
			if (m_CurrentAnimation == "default" || !m_AnimationRunning) return;

			if (m_Animations.find(m_CurrentAnimation) != m_Animations.end())
			{
				if (m_Animations[m_CurrentAnimation].CurrentFrameTime > 0.f)
				{
					m_Animations[m_CurrentAnimation].CurrentFrameTime -= n2dDeltaTime;
				}
				else
				{
					m_Animations[m_CurrentAnimation].CurrentFrameTime = m_Animations[m_CurrentAnimation].TimeBetweenFramesMS;
					
					m_Animations[m_CurrentAnimation].CurrentFrame++;
					if (m_Animations[m_CurrentAnimation].CurrentFrame > m_Animations[m_CurrentAnimation].EndFrame)
					{
						if (m_Animations[m_CurrentAnimation].Loop)
						{
							m_Animations[m_CurrentAnimation].CurrentFrame = m_Animations[m_CurrentAnimation].StartFrame;
						}
						else
						{
							if(m_Animations[m_CurrentAnimation].OnAnimationEnd)
								m_Animations[m_CurrentAnimation].OnAnimationEnd(this);
					
							m_AnimationRunning = false;
						}
					}
				}
			}
			else
			{
				LOG(LVL_W, "Trying to tick animation: " + m_CurrentAnimation + " but animation by this name does not exists.");
			}

		}

		// ------------------------------------------

		void Sprite::Update()
		{

		}

		void Sprite::Flip(SDL_RendererFlip flip)
		{
			m_Flip = flip;
		}

		void Sprite::Scale(float scale)
		{
			m_Scale = scale;
			m_DestRect.w = m_FrameSize.x * scale;
			m_DestRect.h = m_FrameSize.y * scale;
		}

		void Sprite::Draw(float oX, float oY)
		{
			if (!m_Visible || !m_Alive) return;

			// At this moment Sprite sheets must be horizontal strips
			if (m_Animations.find(m_CurrentAnimation) != m_Animations.end())
			{
				m_SrcRect.x = m_Animations[m_CurrentAnimation].CurrentFrame * m_FrameSize.x;
			}
			else
			{
				m_SrcRect.x = m_FrameSize.x;
			}

			m_SrcRect.w = m_FrameSize.x;

			m_DestRect.x = (int)(m_Position.x + oX);
			m_DestRect.y = (int)(m_Position.y + oY);

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, &m_SrcRect, &m_DestRect, m_Angle, NULL, m_Flip);
		}

		bool Sprite::operator==(const Sprite& other)
		{
			return m_ID == other.m_ID;
		}

		void Sprite::DestroySelf()
		{
			m_Alive = 0;

			n2dRemoveDrawable(m_ID, m_Layer);

			SetDeleted(true);
		}
	}
}