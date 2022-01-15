#include "SimpleBulletController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleBulletController::SimpleBulletController(Vec2 start, Vec2 end, const float moveUpdateDelay)
			: m_AliveBounds(Rect(0,0,0,0))
		{
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;
			m_Start = start;
			m_End = end;

			m_AliveBounds = Rect(0, 0, Game::s_Width, Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			Game::AddUpdater(std::bind(&SimpleBulletController::Update, this));
		}

		SimpleBulletController::~SimpleBulletController()
		{
			if (m_Sprite)
				delete m_Sprite;

			Game::RemoveUpdater(std::bind(&SimpleBulletController::Update, this));
		}

		void SimpleBulletController::AddSprite(Vec2 position, const char* spriteSheet, Vec2 size, char layer)
		{
			m_Sprite = new Sprite(position, spriteSheet, size);
			Game::s_Renderer->s_DrawLayers->AddSprite(m_Sprite, layer);
		}

		void SimpleBulletController::Configure(int moveSpeed, Rect aliveBounds)
		{
			m_MoveSpeed = moveSpeed;
			m_AliveBounds = aliveBounds;
		}

		void SimpleBulletController::Update()
		{
			if (OutOfBounds())
			{
				LOG("Out of bounds: bullet");
				return;
			}

			if (m_DelayTime > 0)
			{
				m_DelayTime -= Game::s_DeltaTime;
				return;
			}

			m_DelayTime = m_UpdateDirectionDelay;

			int x = m_Sprite->GetX();
			int y = m_Sprite->GetY();

			int dx = x < m_End.x ? x + m_MoveSpeed : x - m_MoveSpeed;
			int dy = y < m_End.y ? y + m_MoveSpeed : y - m_MoveSpeed;

			if (x = m_End.x) dx = x;
			if (y = m_End.y) dy = y;

			m_Sprite->SetPosition(dx, dy);

		}

		bool SimpleBulletController::OutOfBounds()
		{
			if (m_Sprite)
			{
				int x = m_Sprite->GetX();
				int y = m_Sprite->GetY();
				int w = m_Sprite->GetWidth();
				int h = m_Sprite->GetHeight();

				int bx = m_AliveBounds.x;
				int by = m_AliveBounds.y;
				int bw = m_AliveBounds.w;
				int bh = m_AliveBounds.h;

				return !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
			}

			return true;
		}
	}
}