#pragma once
#include "SimpleController.h"
#include <functional>
#include "../maths/Rect.h"
#include "../core/BoundUser.h"

typedef std::function<void()> f_VoidFunction;

namespace novazero
{
	namespace controllers
	{
		using namespace core;

		class UDRLController : 
			public SimpleController, 
			public BoundUser
		{

		private:

		public:

			UDRLController(std::string spriteSheet, Vec2Int position, Vec2Int size, char layer);
			~UDRLController();

			void ConfigureMove(int moveSpeed);

			void MoveUp();
			void MoveDown();
			void MoveRight();
			void MoveLeft();

			void DestroySelf() override;

		};
	}
}