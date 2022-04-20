#pragma once
#include "../physics/PhySprite.h"
#include "../components/SimpleStatBar.h"
#include "../graphics/Image.h"

namespace novazero
{
	namespace controllers
	{
		using namespace novazero::physics;
		using namespace novazero::components;
		using namespace novazero::graphics;

		class BasicController
			: public PhySprite
		{

		private:

			SimpleStatBar* m_HealthBar = nullptr;
			float m_Health = 100.f;

			bool m_JoystickEnabled = false;
			char m_JoystickControllerID = -1;

			bool m_ArrowKeysEnabled = false;
			bool m_WASDEnabled = false;

			void ArrowKeys();
			void WASD();

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

			void ControllerUpdate();
			void Controls();

		public:

			BasicController(const std::string& assetName, const std::string& colliderName,
				Vec2 position, Vec2 colliderSize, Vec2Int spriteSize, unsigned char layer);

			void EnableWASD(bool val);
			void EnableArrowKeys(bool val);
			void EnableRotation(bool val);

			void EnabledJoystickController(bool val, char controllerID);
			void JoystickControllers();

			void Hurt(float damage);

			void DestroySelf();

		};
	}
}