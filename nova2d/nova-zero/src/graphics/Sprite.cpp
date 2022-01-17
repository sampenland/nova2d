#include "Sprite.h"

namespace novazero
{
	namespace graphics
	{
		using namespace core;
		using namespace utils;
		using namespace logging;

		Sprite::Sprite(std::string assetName, Vec2Int position, Vec2Int frameSize, char layer)
			: m_ID(0), m_Layer(0), m_SrcRect(SDL_Rect()), m_DestRect(SDL_Rect())
		{
			m_Position = position;

			m_Angle = 0;
			m_Layer = layer;

			m_FrameWidth = frameSize.x;
			m_FrameHeight = frameSize.y;

			m_Frames = 1;
			
			m_AssetName = assetName;
			m_SpriteSheet = Game::s_AssetManager->GetTexture(assetName);

			// Draw setup
			m_SrcRect.x = 0;
			m_SrcRect.y = 0;
			m_SrcRect.w = (int)frameSize.x;
			m_SrcRect.h = (int)frameSize.y;
			m_DestRect.w = (int)frameSize.x;
			m_DestRect.h = (int)frameSize.y;

			// Final
			m_ID = Game::s_IDCount;
			Game::s_IDCount++;
			Game::s_Renderer->s_DrawLayers->AddSprite(this, m_Layer);
		}

		Sprite::~Sprite()
		{
			if (m_SpriteSheet)
			{
				m_SpriteSheet = NULL;
			}
			
			if (m_NextFrameTimer)
			{
				delete m_NextFrameTimer;
				m_NextFrameTimer = NULL;
			}

			Game::s_Renderer->s_DrawLayers->RemoveSprite(m_ID, m_Layer);
		}

		void Sprite::ConfigureAnimation(int frames, float delayBetweenFrames, bool looping) 
		{
			m_Frames = frames;

			m_AnimationRunning = true;
			
			if (m_NextFrameTimer)
			{
				delete m_NextFrameTimer;
				m_NextFrameTimer = NULL;
			}

			m_NextFrameTimer = new Timer(delayBetweenFrames, looping, std::bind(&Sprite::NextFrame, this));
		}

		void Sprite::NextFrame()
		{
			if (m_AnimationRunning)
			{
				m_CurrentFrame++;
				if (m_CurrentFrame >= m_Frames - 1)
				{
					m_CurrentFrame = 0;
				}
			}
		}

		void Sprite::SetFrame(int frame)
		{
			if (frame < m_Frames && frame >= 0)
				m_Frames = frame;
		}

		void Sprite::Draw()
		{
			if (!m_Visible) return;

			m_SrcRect.x = m_CurrentFrame * m_FrameWidth;
			m_DestRect.x = m_Position.x;
			m_DestRect.y = m_Position.y;

			SDL_RenderCopyEx(Game::s_Renderer->GetSDLRenderer(), m_SpriteSheet, &m_SrcRect, &m_DestRect, m_Angle, NULL, SDL_FLIP_NONE);
		}

		bool Sprite::operator==(const Sprite& other)
		{
			return m_ID == other.m_ID;
		}
	}
}