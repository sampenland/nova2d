#pragma once
#include <functional>
#include "../physics/Collision.h"
#include "SDL.h"

enum JoystickAxis
{
	JOY_STICK_AXIS_X = 0,
	JOY_STICK_AXIS_Y = 1
};

typedef std::function<void()> f_VoidFunction;
typedef std::function<void(float)> f_FloatPassFunction;
//typedef std::function<void(Collision)> f_CollisionPassFunction;

typedef std::function<bool(SDL_Keycode)> f_ConditionalFunction;
typedef std::function<bool(int, int)> f_JoyStickConditionalFunction;
typedef std::function<float(char, JoystickAxis)> f_JoyStickAxisConditionalFunction;