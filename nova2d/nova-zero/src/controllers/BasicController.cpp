#include "BasicController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		BasicController::BasicController(const std::string& assetName, const std::string& colliderName,
			Vec2 position, Vec2 colliderSize, Vec2Int spriteSize, unsigned char layer)
			: PhySprite(assetName, position, colliderSize, layer, spriteSize, colliderName)
		{
			auto cid = n2dAddUpdater(BasicController::ControllerUpdate, this);
			m_CleanUpdaters.push_back(cid);

			m_HealthBar = new SimpleStatBar(true, 0, 0, 5, 32, "black", "black",
				"green", 4);
			m_HealthBar->ConfigureForeground("green", "yellow", "red");
		}

		void BasicController::EnableArrowKeys(bool val)
		{
			m_ArrowKeysEnabled = val;
		}

		void BasicController::EnableMove(bool val)
		{
			m_MoveEnabled = val;
		}

		void BasicController::EnableWASD(bool val)
		{
			m_WASDEnabled = val;
		}

		void BasicController::EnabledJoystickController(bool val, char controllerID)
		{
			if (controllerID >= SDL_NumJoysticks())
			{
				LOG(LVL_FATAL_ERROR, "A controller was not found, may cause unplayable game.", __FILE__, __LINE__);
				return;
			}

			m_JoystickEnabled = val;
			m_JoystickControllerID = controllerID;
		}

		void BasicController::EnableRotation(bool val)
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					GetPhySprite()->GetBody()->SetFixedRotation(!val);
				}
			}
		}

		void BasicController::ConfigureMoveSpeed(float speed)
		{
			m_MoveSpeed = speed;
		}

		void BasicController::ConfigureMaxVelocity(Vec2 max)
		{
			m_MaxVelocity = max;
		}

		void BasicController::ConfigureMaxVelocity(float max)
		{
			m_MaxVelocity = Vec2(max, max);
		}

		bool BasicController::GetMoving() const
		{
			return m_Moving;
		}

		bool BasicController::GetBodyMoving(float percentMinMovement)
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					b2Vec2 vel = GetPhySprite()->GetBody()->GetLinearVelocity();
					percentMinMovement *= m_MoveSpeed;
					return vel.x > percentMinMovement || vel.x < -percentMinMovement || 
						vel.y > percentMinMovement || vel.y < -percentMinMovement;
				}
			}
		}

		void BasicController::ControllerUpdate()
		{
			m_HealthBar->Update((int)(m_Health / 100 * 32), (int)(GetX() + GetWidth() + 5), (int)(GetY()));

			if (m_MoveEnabled)
			{
				Controls();
			}
		}

		void BasicController::Controls()
		{
			m_Moving = false;
			ArrowKeys();
			WASD();
			JoystickControllers();

			if (!m_Moving)
			{
				m_MoveDirection = Directions::None;
			}

		}

		void BasicController::JoystickControllers()
		{
			if (!m_JoystickEnabled) return;

			bool up = n2dJoySimpleUp(m_JoystickControllerID);
			bool down = n2dJoySimpleDown(m_JoystickControllerID);
			bool right = n2dJoySimpleRight(m_JoystickControllerID);
			bool left = n2dJoySimpleLeft(m_JoystickControllerID);

			if (up)
			{
				MoveUp();
			}

			if (down)
			{
				MoveDown();
			}

			if (left)
			{
				MoveLeft();
			}

			if (right)
			{
				MoveRight();
			}
		}

		void BasicController::WASD()
		{
			if (!m_WASDEnabled) return;

			bool up = n2dIsKeyDown(SDLK_w);
			bool down = n2dIsKeyDown(SDLK_s);
			bool right = n2dIsKeyDown(SDLK_d);
			bool left = n2dIsKeyDown(SDLK_a);

			if (up)
			{
				MoveUp();
			}

			if (down)
			{
				MoveDown();
			}

			if (left)
			{
				MoveLeft();
			}

			if (right)
			{
				MoveRight();
			}
		}

		void BasicController::ArrowKeys()
		{
			if (!m_ArrowKeysEnabled) return;

			bool up = n2dIsKeyDown(SDLK_UP);
			bool down = n2dIsKeyDown(SDLK_DOWN);
			bool right = n2dIsKeyDown(SDLK_RIGHT);
			bool left = n2dIsKeyDown(SDLK_LEFT);

			if (up)
			{
				MoveUp();
			}

			if (down)
			{
				MoveDown();
			}

			if (left)
			{
				MoveLeft();
			}

			if (right)
			{
				MoveRight();
			}
		}

		void BasicController::MoveUp()
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					b2Vec2 v = GetPhySprite()->GetBody()->GetLinearVelocity();
					if (v.y < -m_MaxVelocity.y)
						return;
				}
			}

			ApplyForce(m_MoveSpeed * n2dTimeScale, Directions::Up);
			m_MoveDirection = Directions::Up;
			m_Moving = true;
		}

		void BasicController::MoveDown()
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					b2Vec2 v = GetPhySprite()->GetBody()->GetLinearVelocity();
					if (v.y > m_MaxVelocity.y)
						return;
				}
			}

			ApplyForce(m_MoveSpeed * n2dTimeScale, Directions::Down);
			m_MoveDirection = Directions::Down;
			m_Moving = true;
		}

		void BasicController::MoveRight()
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					b2Vec2 v = GetPhySprite()->GetBody()->GetLinearVelocity();
					if (v.x > m_MaxVelocity.x)
						return;
				}
			}

			ApplyForce(m_MoveSpeed * n2dTimeScale, Directions::Right);
			m_MoveDirection = Directions::Right;
			m_Moving = true;
		}

		void BasicController::MoveLeft()
		{
			if (GetPhySprite())
			{
				if (GetPhySprite()->GetBody())
				{
					b2Vec2 v = GetPhySprite()->GetBody()->GetLinearVelocity();
					if (v.x < -m_MaxVelocity.x)
						return;
				}
			}

			ApplyForce(m_MoveSpeed * n2dTimeScale, Directions::Left);
			m_MoveDirection = Directions::Left;
			m_Moving = true;
		}

		Directions BasicController::GetDirection() const
		{
			return m_MoveDirection;
		}

		void BasicController::Hurt(float damage)
		{
			m_Health -= damage;
		}

		void BasicController::DestroySelf()
		{
			CleanUpdaters();
			PhySprite::DestroySelf();
		}
	}
}