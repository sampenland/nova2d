#pragma once
#include <functional>
#include "SDL.h"

// Max gamepads
#define MAX_JOYSTICKS 8

// Max draw layers
#define MAX_LAYERS 20

// Random int between min-max
#define randomi(min, max) (int)(rand() % min + max)

// Random float between min-max
#define randomf(LO, HI) LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)))

enum JoystickAxis
{
	JOY_STICK_AXIS_X = 0,
	JOY_STICK_AXIS_Y = 1
};

typedef std::function<void()> f_VoidFunction;
typedef std::function<void(float)> f_FloatPassFunction;

typedef std::function<bool(SDL_Keycode)> f_ConditionalFunction;
typedef std::function<bool(int, int)> f_JoyStickConditionalFunction;
typedef std::function<float(char, JoystickAxis)> f_JoyStickAxisConditionalFunction;
