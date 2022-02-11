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

			LinkPositionalSprite(this);

			// Final
			m_ID = Game::GetNextID();
			n2dAddDrawable(this, m_Layer);
		}

		void Sprite::ConfigureAnimation(int startFrame, int animationLength, int totalFrames, float animationSpeed, bool loop)
		{
			m_Frames = totalFrames;
			m_AnimationLength = animationLength;
			m_CurrentFrame = startFrame;
			m_StartFrame = startFrame;

			if (m_CurrentFrame >= m_Frames) m_CurrentFrame = 0;

			if (m_AnimationTimer)
			{
				delete m_AnimationTimer;
			}

			m_AnimationLooping = loop;
			m_AnimationTimer = new Timer(animationSpeed, loop, std::bind(&Sprite::NextFrame, this));

		}

		void Sprite::JumpToFrame(int frame)
		{
			if (frame < m_Frames)
				m_CurrentFrame = frame;
		}

		void Sprite::NextFrame()
		{
			if (!m_Visible || !m_Alive) return;

			m_CurrentFrame++;

			if (m_CurrentFrame >= m_StartFrame + m_AnimationLength)
			{
				if (m_AnimationLooping)
				{
					m_CurrentFrame = m_StartFrame;
				}
				else
				{
					m_CurrentFrame = m_Frames - 1;
				}

				if (f_OnAnimationEnd)
					f_OnAnimationEnd(this);
			}
		}

		void Sprite::Update()
		{

		}

		void Sprite::Flip(SDL_RendererFlip flip)
		{
			m_Flip = flip;
		}

		void Sprite::Draw(float oX, float oY)
		{
			if (!m_Visible || !m_Alive) return;

			m_SrcRect.x = m_CurrentFrame * m_FrameSize.x;
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

			if (m_AnimationTimer)
				m_AnimationTimer->DestroySelf();

			n2dRemoveDrawable(m_ID, m_Layer);

			SetDeleted(true);
		}
	}
}