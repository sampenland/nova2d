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

		Sprite::Sprite(std::string assetName, Vec2Int position, Vec2Int size, char layer)
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

		void Sprite::ConfigureAnimation(int startFrame, int totalFrames, float animationSpeed, bool loop)
		{
			m_Frames = totalFrames;
			m_CurrentFrame = startFrame;
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

			if (m_CurrentFrame >= m_Frames)
			{
				if (m_AnimationLooping)
				{
					m_CurrentFrame = 0;
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

		void Sprite::Draw()
		{
			if (!m_Visible || !m_Alive) return;

			m_SrcRect.x = m_CurrentFrame * m_FrameSize.x;
			m_SrcRect.w = m_FrameSize.x;

			m_DestRect.x = m_Position.x;
			m_DestRect.y = m_Position.y;

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, &m_SrcRect, &m_DestRect, m_Angle, NULL, SDL_FLIP_NONE);
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

			m_DeleteNow = 1;
		}
	}
}