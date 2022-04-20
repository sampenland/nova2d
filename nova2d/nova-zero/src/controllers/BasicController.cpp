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

		void BasicController::EnableWASD(bool val)
		{
			m_WASDEnabled = val;
		}

		void BasicController::EnabledJoystickController(bool val, char controllerID)
		{
			if (controllerID >= SDL_NumJoysticks())
			{
				LOG(LVL_FATAL_ERROR, "A controller was not found, may cause unplayable game.");
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
					GetPhySprite()->GetBody()->SetFixedRotation(val);
				}
			}
		}

		void BasicController::ControllerUpdate()
		{
			m_HealthBar->Update(m_Health / 100 * 32, GetX() + GetWidth() + 5, GetY());

			Controls();
		}

		void BasicController::Controls()
		{
			ArrowKeys();
			WASD();
			JoystickControllers();
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
			ApplyForce(100, Directions::Up);
		}

		void BasicController::MoveDown()
		{
			ApplyForce(100, Directions::Down);
		}

		void BasicController::MoveRight()
		{
			ApplyForce(100, Directions::Right);
		}

		void BasicController::MoveLeft()
		{
			ApplyForce(100, Directions::Left);
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